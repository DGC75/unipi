#define _GNU_SOURCE
#include <stdio.h>
#include <stdlib.h>
#include <errno.h>
#include <pthread.h>
#include <string.h>

typedef struct string{
    char *str;
    struct string *next;
    struct string *last;
}String;


String *q_line = NULL;
String *q_words = NULL;

void enqueue(String** q, char *item){
    
    String *new = calloc(1, sizeof(String));
    if(new == NULL){
        perror("calloc");
        exit(EXIT_FAILURE);
    }

    new->str = item;
    new->next = NULL;
    new->last = new;

    if(q == NULL){
        puts("enq: q==NULL");
        free(new);
        exit(EXIT_FAILURE);
    }

    if(*q == NULL){
        *q = new;

    }
    else{
        String *tmp = *q;
        *q = new;
        new->next = tmp;
        new->last = tmp->last;
    }

    return;
}

char* dequeue(String** q){

    char *str = NULL;
    if(q == NULL){
        puts("deq: q== NULL");
        exit(EXIT_FAILURE);
    }
    if(*q == NULL){
        puts("deq: *q== NULL");
        exit(EXIT_FAILURE);
    }
    else{
        str = (*q)->str;
        String *toDeq = *q;
        (*q) = (*q)->next;
        free(toDeq);
    }
    return str;
}

pthread_mutex_t mtx_ql = PTHREAD_MUTEX_INITIALIZER;
pthread_mutex_t mtx_qw = PTHREAD_MUTEX_INITIALIZER;

int l_is_active = 0;

int wait_new_data_ql = 1;
int wait_new_data_qw = 1;

void mtx_lock(pthread_mutex_t *mtx_ptr){
    int err;
    if((err = pthread_mutex_lock(mtx_ptr)) != 0){
        puts("mutex_lock");
        errno = err;
        pthread_exit(&errno);
    }
    else{
        //puts("mutex locked");
    }
}

void mtx_unlock(pthread_mutex_t *mtx_ptr){
    int err;
    if((err = pthread_mutex_unlock(mtx_ptr)) != 0){
        perror("mutex_unlock");
        errno = err;
        pthread_exit(&errno);
    }
    else{
        //puts("mutex unlocked");
    }
}

static void*parseDoc(void *arg){

    char *line = NULL;
    size_t len = 0;
    ssize_t nread;
    char *fileName = (char*)arg;

    FILE *file = fopen(fileName, "r");
    if(file == NULL){
        perror("fopen");
        exit(EXIT_FAILURE);
    }

    wait_new_data_ql = 1;

    while ((nread = getline(&line, &len, file)) != -1) {
        l_is_active = 1;
        mtx_lock(&mtx_ql);
        enqueue(&q_line, line);
        mtx_unlock(&mtx_ql);
        len = 0;
    }


    wait_new_data_ql = 0;
    l_is_active = 0;
    free(line);
    fclose(file);
    puts("parsedoc finito");
    fflush(stdout);
    return NULL;
}

static void*parseLine(void *arg){

    char* line;
    char *state;

    wait_new_data_qw = 1;
    
    while((!l_is_active) && (q_line == NULL));

    while((wait_new_data_ql != 0) || (q_line != NULL)){
        puts("q");
        mtx_lock(&mtx_ql);
        line = dequeue(&q_line);
        printf("line:%s\n", line);
        fflush(stdout);
        mtx_unlock(&mtx_ql);

        char *word = strtok_r(line, " ", &state);
        while(word != NULL){

            mtx_lock(&mtx_qw);
            enqueue(&q_words, word);
            mtx_unlock(&mtx_qw);

            word = strtok_r(NULL, " ", &state);
        }

        free(line);
    }
    

    wait_new_data_qw = 0;
    return NULL;
}

static void*printWords(void *arg){
    
    puts("3 l");
    char *word;



    while((wait_new_data_qw != 0) || (q_words != NULL)){
        mtx_lock(&mtx_qw);
        word = dequeue(&q_words);

        mtx_unlock(&mtx_qw);

        printf("Received:%s\n", word);
        free(word);
    }

    return NULL;
}

int main (int argc, char *argv[]){
    
    pthread_t parseDocTh, parseLineTh, printWordsTh;
    //CREA THREAD

    int errpD, errpL, errpW;

    if((errpD = pthread_create(&parseDocTh, NULL, parseDoc, (void *)(argv[1]))) != 0)
        perror("pthread create");

    if((errpL = pthread_create(&parseLineTh, NULL, parseLine, NULL)) != 0)
        perror("pthread create");
    
    if((errpW = pthread_create(&printWordsTh, NULL, printWords, NULL)) != 0)
        perror("pthread create");



    pthread_join(parseDocTh, NULL);
    pthread_join(parseLineTh, NULL);
    pthread_join(printWordsTh, NULL);

    return 0;
}
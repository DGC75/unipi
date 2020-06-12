#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_STR_LEN 102

typedef struct node{
    char* name;
    struct node* next;
}Node;

typedef Node* List;
typedef List Queue;

int get_int();
void mem_err();


void print_queue(Queue q){
    while(q != NULL){
        printf("'%s'\n", q->name);
        q = q->next;
    }
}

void add_paziente(Queue* q_ptr);
void dequeue(Queue* q_ptr);
char** reorder_queue(Queue *q_ptr, int* dim);
void print_str_arr(char** str_arr, int dim);
void free_arr_str(char ** str_arr, int dim);
Node* load_new_node();
int count_queue(Queue q);
int str_cmp(const void* p1,const void* p2);


int main(){

    /*DICHIARA CODA VUOTA*/
    Queue coda_pazienti = NULL;

    

    /*ENTRA IN UN LOOP*/
        /*e = 0*/
            /*ESCI DALLA CODA*/
        /*e = 1*/
            /*AGGIUNGI PAZIENTE ALLA CODA*/
        /*e = 2*/
            /*RIMUOVI PAZIENTE DALLA CODA*/
    int e = get_int();
    while(e != 0){
        
        if(e == 1)
            add_paziente(&coda_pazienti);
        else if(e == 2)
            dequeue(&coda_pazienti);
        

        e = get_int();
    }
    /*RIORDINA LA CODA METTENDOLA IN UN ARRAY*/
    /*DEALLOCA LA CODA*/
    int dim = 0;
    char** arr = reorder_queue(&coda_pazienti, &dim);

    /*STAMPA GLI EL. DELLA CODA IN ORDINE ALFABETICO*/
    print_str_arr(arr, dim);

    /*DEALLOCA ARRAY DI STRINGHE*/
    free_arr_str(arr, dim);

    return 0;
}

void add_paziente(Queue* q_ptr){
    if(q_ptr != NULL){

        Node *new_paziente = load_new_node();
        
        if(*q_ptr == NULL){
            *q_ptr = new_paziente;
            return;
        }

        while ((*q_ptr)->next != NULL){
            q_ptr = &((*q_ptr)->next);
        }

        (*q_ptr)->next = new_paziente;
    }
}

void dequeue(Queue* q_ptr){
    if(q_ptr != NULL && (*q_ptr) != NULL){
        Node* tmp = *q_ptr;

        (*q_ptr) = (*q_ptr)->next;

        free(tmp->name);
        free(tmp);
    }
}

char** reorder_queue(Queue *q_ptr, int* dim){
    
    int n = count_queue(*q_ptr);
    char** str_arr = calloc(n, sizeof(char*));

    if(str_arr == NULL)
        mem_err();
    
    Node* tmp = NULL;
    int i;
    for(i = 0; i < n; i++){

        str_arr[i] = (*q_ptr)->name;

        tmp = *q_ptr;
        if((*q_ptr)->next != NULL)
            q_ptr = &((*q_ptr)->next);
        
        free(tmp);
    }


    qsort(str_arr, n, sizeof(char*), str_cmp);

    *dim = n;
    return str_arr;

}

int str_cmp(const void* p1,const void* p2){
    
    char** s1 = (char**) p1;
    char** s2 = (char**) p2;

    return strcmp(*s1, *s2);
}

void print_str_arr(char** str_arr, int dim){
    int i;
    for(i = 0; i < dim; i++)
        printf("%s\n", str_arr[i]);
    
    puts("$");
}


void free_arr_str(char ** str_arr, int dim){
    int i;
    for(i = 0; i < dim; i++){
        free(str_arr[i]);
        str_arr[i] = NULL;
    }
    free(str_arr);
    str_arr = NULL;   
}


int count_queue(Queue q){
    int n = 0;
    while(q != NULL){
        n+=1;
        q=q->next;
    }
    return n;
}

Node* load_new_node(){

    Node* tmp = calloc(1, sizeof(Node));
    if(tmp == NULL)
        mem_err();

    char str[MAX_STR_LEN] = {'\0'};
    fgets(str, MAX_STR_LEN, stdin);

    str[strlen(str)-1] = '\0';

    int len = strlen(str);

    char* tmp_str = calloc(len+1, sizeof(char));
    
    if(tmp_str == NULL)
        mem_err();
    
    strncpy(tmp_str, str ,len+1);

    tmp->name = tmp_str;

    return tmp;
}

int get_int(){
    int tmp;
    scanf("%d", &tmp);
    scanf("%*[^\n]");
    scanf("%*c");

    return tmp;
}

void mem_err(){
    puts("memoria heap esaurita");
    exit(EXIT_FAILURE);
}
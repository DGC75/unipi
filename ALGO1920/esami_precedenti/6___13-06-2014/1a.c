#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_STR_LEN 101

typedef struct esame{
    int selected;
    char *name;
    int credits;
    int difficulty;
}Esame;

int get_int();
void mem_err();
char* alloc_str(int dim);

int min_stress(const void* a, const void* b);
void load_exam_list(Esame* arr, int dim);
void print_list_exams(Esame* arr, int N, int K);

void print_list(Esame*arr, int dim){
    int i;
    for(i = 0; i < dim; i++){
        printf("%s\n", arr[i].name);
    }
    puts("");
}

Esame* alloc_struct_arr(int dim);

int main(){
    /*LEGGI K, TOTALE ESATTO CREDITI*/
    /*LEGGI N, TOTALE ESATTO ESAMI POSSIBILI*/

    /*ALLOCA UN ARR DI N ESAMI E INSERISCI IN ORDINE DI INSERIMENTO*/
    /*SI ORDINA SECONDO IL CRITERIO*/
    /*SI ORDINANO PER CREDITI, IN MODO NON CRESCENTE*/
        /*A PARITA' DI CREDITI, SI ORDINA PER DIFFICOLTA' CRESCENTE*/
            /*A PARITA' DI DIFFICOLTA' SI ORDINA PER ORDINE LESSICOGRAF. NON DECR.*/
    


    int K = get_int();
    int N = get_int();

    Esame* exam_arr = alloc_struct_arr(N);

    load_exam_list(exam_arr, N);
    qsort(exam_arr, N, sizeof(Esame), min_stress);

    print_list_exams(exam_arr, N, K);


    /*BISOGNA LIBERARE ANCHE LE STRINGHE ALLOCATE*/
    int i;
    for(i = 0; i < N; i++){
        free(exam_arr[i].name);
    }
    free(exam_arr);

    return 0;
}

void load_exam_list(Esame* arr, int dim){
    
    char str[MAX_STR_LEN] = {'\0'};
    
    int i;
    for(i = 0; i < dim; i++){
        
        fgets(str, MAX_STR_LEN, stdin);
        str[strlen(str) - 1] = '\0';

        char *new_str = alloc_str(strlen(str) + 1);
        strncpy(new_str,str, strlen(str)+1);
        arr[i].name = new_str;
        arr[i].credits = get_int();
        arr[i].difficulty = get_int();

    }
}

int lexgraph(const void *p1, const void *p2){
    
    Esame* a = (Esame*) p1;
    Esame* b = (Esame*) p2;

    if(a->selected > b->selected)
        return 1;
    else if( a->selected == b->selected){
        if(a->selected == 1){
            return strcmp(a->name, b->name);
        }
        return 0;
    }
    else
        return -1;
    
}

void print_list_exams(Esame* arr, int N, int K){
    
    int i = 0;
    int total = 0;
    while(total <= K && i < N){
        if((total + arr[i].credits) <= K){
            total += arr[i].credits;
            arr[i].selected = 1;
        }
        if(total == K)
            break;
        
        ++i;       
    }

    qsort(arr, N, sizeof(Esame), lexgraph);
    i = 0;
    total = 0;

    while(total <= K && i < N){
        if((total + arr[i].credits) <= K && arr[i].selected == 1){
            total += arr[i].credits;
            printf("%s\n", arr[i].name);
        }
        if(total == K)
            break;
        
        ++i;       
    }

}

int min_stress(const void* ptr1, const void* ptr2){
        
    Esame* a = (Esame*) ptr1;
    Esame* b = (Esame*) ptr2;

    if(a->credits < b->credits)
        return 1;
    else if(a->credits == b->credits){
        if(a->difficulty < b->difficulty)
            return -1;
        else if(a->difficulty == b->difficulty){
            return strcmp(a->name, b->name);
        }
        else
            return 1;

    }
    else
        return -1;
}

char* alloc_str(int dim){
    char* tmp = calloc(dim, sizeof(char));

    if(tmp == NULL)
        mem_err();

    return tmp;
}


Esame* alloc_struct_arr(int dim){
    
    Esame* tmp = calloc(dim, sizeof(Esame));
    
    if(tmp == NULL)
        mem_err();

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
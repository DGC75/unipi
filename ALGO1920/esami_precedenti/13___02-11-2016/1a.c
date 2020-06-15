#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct el{
    int val;
    int count;
    struct el* next;

} Element;

typedef Element* List;
typedef List* Hash_table;

int get_int();
void mem_err();

void free_list(List lst);
int query_ht(Hash_table ht, int dim_arr,int val,int check_val);

int* load_arr(int dim);
Hash_table load_ht(Hash_table ht, int* arr, int dim);
void print_query_arr(int* arr, int dim, Hash_table ht, int K);
void free_ht(Hash_table ht, int dim);
Hash_table alloc_ht(int dim);
void insert_ht(Hash_table ht, int dim, int el);
Element* load_el(int val);

int hash(int el, int N);

void print_arr(int* arr, int dim){
    int i;
    for(i = 0; i < dim; i++)
        printf("%d ", arr[i]);
    
    puts("");
}

void print_list(List lst){
    while(lst != NULL){
        printf("el:%d count:%d\n",lst ->val, lst->count);
        lst = lst->next;
    }
}

void print_ht(Hash_table ht, int dim){
    int i;
    for(i = 0; i < dim; i++){

        if( (*ht + i) != NULL){
            print_list(ht[i]);
        }
    }
}



int main(){

    /*LEGGI N E K*/
    /*ACQUISISCI ARRAY DI N INTERI*/
    /*SCANSIONA E INSERISCI IN UNA TABELLA HASH, CONTANDO LE OCCORRENZE*/
    /*E SALVANDOLE IN UN PARAMETRO*/
    /*SCORRI L'ARRAY E STAMPA SOLO GLI ELEMENTI CHE APPAIONO ALMENO K VOLTE (>=)*/
    /*DEALLOCA ARRAY E TABELLA HASH*/

    int N, K;
    scanf("%d %d", &N, &K);
    scanf("%*c");

    int*arr = load_arr(N);

    Hash_table ht = NULL;

    ht = load_ht(ht, arr, N);

    print_query_arr(arr, N, ht, K);

    free_ht(ht, 2*N);
    ht = NULL;
    free(arr);
    arr = NULL;

    return 0;
}

void print_query_arr(int* arr, int dim, Hash_table ht, int K){
    int i;
    for(i = 0; i < dim; i++){
        if(query_ht(ht, dim, arr[i], K) == 1)
            printf("%d ", arr[i]);
    }
    puts("");
}

int query_ht(Hash_table ht, int dim_arr,int val,int check_val){
    int h = hash(val, dim_arr);

    List lst = ht[h];

    while(lst != NULL && lst->val != val)
        lst = lst->next;
    
    if(lst == NULL)
        return 0;
    else{
        if((lst->val == val) && (lst->count) >= check_val)
            return 1;
        else
            return 0;
    }
}

int* load_arr(int dim){
    
    int* tmp = calloc(dim, sizeof(int));
    
    if(tmp == NULL)
        mem_err();
    
    int i;
    for(i = 0; i < dim; i++)
        scanf("%d", &(tmp[i]));

    scanf("%*c");

    return tmp;
}


Hash_table load_ht(Hash_table ht, int* arr, int dim){
    /*ALLOCA TABELLA DI LISTE DI DIMENSIONE 2*N */
    /*PER OGNI EL. DELL'ARRAY*/
        /*CERCALO NELLA TABELLA*/
            /*SE PRESENTE, INCREMENTA IL COUNT DI 1*/
            /*ALTRIMENTI, INSERISCILO CON COUNT = 1*/
    
    ht = alloc_ht(2*dim);

    int i;
    for(i = 0; i < dim; i++)
        insert_ht(ht, dim, arr[i]);
    
    return ht;
}

void insert_ht(Hash_table ht, int dim, int el){
    int h_val = hash(el, dim);
    if(ht[h_val] == NULL){
        ht[h_val] = load_el(el);    
    }
    else{
        Element *el_ptr = ht[h_val];
        while ((el_ptr)->next != NULL && el_ptr->val != el)
            el_ptr = el_ptr->next;
        
        if(el_ptr->next == NULL){
            if(el_ptr->val == el)
                el_ptr->count += 1;
            else
                el_ptr->next = load_el(el);
        }
        else
            el_ptr->val += 1;
    }

}

Element* load_el(int val){

    Element *tmp = calloc(1, sizeof(Element));
    
    if(tmp == NULL)
        mem_err();
    
    tmp->count = 1;
    tmp->val = val;

    return tmp;
}

int hash(int el, int N){
    return el%(2*N);
}

Hash_table alloc_ht(int dim){
    
    Hash_table tmp = calloc(dim, sizeof(List));
    if(tmp == NULL)
        mem_err();
    
    return tmp;
}


void free_ht(Hash_table ht, int dim){
    int i;
    for(i = 0; i < dim; i++){
        free_list(ht[i]);
    }
    free(ht);
}

void free_list(List lst){
    if(lst != NULL){
        if(lst->next != NULL)
            free_list(lst->next);

        free(lst);
        lst = NULL;
    }
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
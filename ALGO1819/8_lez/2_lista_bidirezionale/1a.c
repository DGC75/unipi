#include <stdio.h>
#include <stdlib.h>

typedef struct node{
    int val;
    struct node* next;
    struct node* precPtr;
}int_node;

typedef int_node* int_lst;

int_node* insert_tail_dlst(int_node **last_ptr);
void      print_rev_dlst(int_lst dlst_last);
int_node* secure_alloc_int_node();
int       get_int();
void      mem_err();

int main(){

    int_lst lst = NULL;
    int_node* lastPtr = NULL;

    

    /*LEGGE N*/
    int N = get_int();


    lastPtr = insert_tail_dlst(&lst);
    /*PER N-1 VOLTE*/
    int i;
    for(i = 0; i < N - 1; i++)
        /*ACQUISISCI INTERO E INSERISCI IN CODA ALLA LISTA*/
        lastPtr = insert_tail_dlst(&lastPtr);

    /*STAMPA IN ORDINE INVERSO*/
    print_rev_dlst(lastPtr);
}

int_node* insert_tail_dlst(int_node **last_ptr){
    
    int_node *newNode = secure_alloc_int_node();

    newNode->val = get_int();
    
    if((*last_ptr) != NULL){
        newNode->precPtr = *last_ptr;
        (*last_ptr)->next = newNode;
        
        return newNode;
    }

    *last_ptr = newNode;
    return newNode;
}

void print_rev_dlst(int_lst dlst_last){
    while(dlst_last->precPtr != NULL){
        printf("%d\n", dlst_last->val);
        dlst_last = dlst_last->precPtr;
    }
    printf("%d\n", dlst_last->val);
}

int_node* secure_alloc_int_node(){
    int_node* tmp = calloc(1, sizeof(int_node));
    if(tmp == NULL)
        mem_err();

    return tmp;
}

void mem_err(){
    puts("memoria heap esaurita");
    exit(EXIT_FAILURE);
}

int get_int(){
    int tmp;
    scanf("%d", &tmp);
    scanf("%*c");
    return tmp;
}
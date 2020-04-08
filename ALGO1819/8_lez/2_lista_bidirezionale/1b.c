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
int       get_int();

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
    
    int_node *newNode = calloc(1, sizeof(int_node));

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

int get_int(){
    int tmp;
    scanf("%d", &tmp);
    return tmp;
}
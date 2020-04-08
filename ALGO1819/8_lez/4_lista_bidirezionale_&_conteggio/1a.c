#include <stdio.h>
#include <stdlib.h>

typedef struct node{
    
    int val;
    int count;
    struct node* prec;
    struct node* next;

}Node;

typedef Node* List;

int     get_int();
Node*   insert_tail_list(int val, List* lst);
int     is_in_list(int i, List* lst);
void    free_lst(List* lst);
void    mem_err();
Node*   sec_alloc_node();

int main(void){
    
    /*ALLOCA LISTA BIDIREZIONALE*/
    List lst = NULL;
    /*LEGGI N*/
    int N = get_int();
    
    /*ACQUISISCI N INTERI*/
    
    Node* last_ptr = insert_tail_list(get_int(), &lst);

    int i;
    for(i = 0; i < N - 1; i++)
        last_ptr = insert_tail_list(get_int(), &last_ptr);

    /*LEGGI i*/
    i = get_int();

    /*FINCHE' i E' in LISTA, AGGIORNA CONTATORE RICERCHE, 
    ORDINA LISTA (DECRESCENTE) RISPETTO AI CONTATORI DI RICERCA*/
    /*SE I NON E' IN LISTA, STAMPA -1 ED ESCI DAL CICLO*/
    while(is_in_list(i, &lst) == 1)
        i = get_int();    

    /*FREE VARI*/
    free_lst(&lst);
}

int get_int(){
    
    int tmp;
    scanf("%d", &tmp);
    scanf("%*c");

    return tmp;
}

Node* insert_tail_list(int val, List* lst){
    
}
int     is_in_list(int i, List* lst);
void    free_lst(List* lst);
void    mem_err();
Node*   sec_alloc_node();
#include <stdio.h>
#include <stdlib.h>

typedef struct node{
    int val;
    struct node* next;
}slst_node;

typedef slst_node* slst; 

slst_node*  sec_alloc_node();
void        mem_err();
int         get_int();
slst_node*  insert_end_slst(slst_node ** last_ptr);
int         is_in_lst(int i, slst* lst);

void        free_lst(slst* lst);

int main(){

    /*DICHIARA LISTA E PUNTATORE ALL'ULTIMA POSIZIONE*/
    slst        lst = NULL;
    slst_node*  last_ptr = NULL;

    /*LEGGI N*/
    int N = get_int();

    /*ACQUISISCI PRIMO INTERO IN LISTA*/
    last_ptr = insert_end_slst(&lst);

    /*PER N-1 VOLTE*/
    int i;
    for(i = 0; i < N - 1; ++i)

        /*ACQUISISCI E INSERISCI IN CODA*/
        last_ptr = insert_end_slst(&last_ptr);
    
    
    /*LEGGE i*/
    i = get_int();
    
        /*SE' i E' NELLA LISTA, STAMPA POSIZIONE, MOVE TO FRONT,*RILEGGI i*/
        /*ALTRIMENTI, STAMPA -1 E TERMINA*/
        while(is_in_lst(i, &lst) == 1)
            i = get_int();
            
    /*FREE STRUTTURE ALLOCATE*/ 
    free_lst(&lst);   
}

void mem_err(){
    puts("memoria heap esaurita.");
    exit(EXIT_FAILURE);
}

int get_int(){
    
    int tmp;
    
    scanf("%d", &tmp);
    scanf("%*c");
    return tmp;
}

slst_node*  insert_end_slst(slst_node ** last_ptr){
    
    slst_node *newNode = sec_alloc_node();
    newNode->val = get_int();

    if( (*last_ptr) != NULL){
        (*last_ptr)->next = newNode;
        return newNode;
    }

    (*last_ptr) = newNode;
    return newNode;
}

slst_node* sec_alloc_node(){
    
    slst_node *tmp = calloc(1, sizeof(slst_node));

    if(tmp == NULL)
        mem_err();

    return tmp;
}

int is_in_lst(int i, slst* lst){
    int pos = 0;

    slst_node* prec_ptr = NULL;
    slst_node* corr_ptr = *lst;

    while(corr_ptr != NULL){
        if( corr_ptr->val == i){
            
            printf("%d\n", pos);

            /*MOVE TO FRONT*/
            if(prec_ptr != NULL){

                prec_ptr->next = corr_ptr->next;
                corr_ptr->next = *lst;
                *lst = corr_ptr;
            }
        
            return 1;
        }
        else{
            
            prec_ptr = corr_ptr;
            corr_ptr = corr_ptr->next;
            pos++;
        }
    }

    puts("-1");
    return -1;
}

void free_lst(slst* lst){
    
    if(lst != NULL && *lst != NULL){
        if((*lst)->next != NULL){
            free_lst(&(*lst)->next);
        }
        free(*lst);
    }
}
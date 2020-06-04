#include <stdio.h>
#include <stdlib.h>

typedef struct node{
    
    int val;
    int count;
    struct node* prec;
    struct node* next;

}Node;

typedef Node* List;

void    print_lst(List lst);
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

    /*FINCHE' i E' in LISTA, AGGIORNA CONTATORE RICERCHE, 
    ORDINA LISTA (DECRESCENTE) RISPETTO AI CONTATORI DI RICERCA*/
    /*SE I NON E' IN LISTA, STAMPA -1 ED ESCI DAL CICLO*/
    
    while(is_in_list(get_int(), &lst) == 1);

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
    
    Node* newNode = sec_alloc_node();
    newNode->val = val;

    if(*lst != NULL){
        newNode->prec = *lst;
        (*lst)->next = newNode;
        return newNode;
    }

    *lst = newNode;
    return newNode;
}


    /*FINCHE' i E' in LISTA, AGGIORNA CONTATORE RICERCHE, 
    ORDINA LISTA (DECRESCENTE) RISPETTO AI CONTATORI DI RICERCA*/
    /*SE I NON E' IN LISTA, STAMPA -1 ED ESCI DAL CICLO*/
int is_in_list(int i, List* lst){

    int pos = 0;

    Node *tmpPtr = NULL;
    Node *corrPtr = *lst;
    
    while(corrPtr != NULL){
        if((corrPtr)->val == i){

            printf("%d\n", pos);
            (corrPtr)->count++;

            /*POSIZIONA IL NODO CORRETTAMENTE*/
            tmpPtr = corrPtr;

            while(tmpPtr->prec != NULL && tmpPtr->prec->count < corrPtr->count)
                tmpPtr = tmpPtr->prec;
            

            if(tmpPtr != corrPtr){
                
                /*SMONTA NODO*/
                if(corrPtr->next != NULL)
                    corrPtr->next->prec = corrPtr->prec;
                
                if(corrPtr->prec != NULL)
                    corrPtr->prec->next = corrPtr->next;

                if(tmpPtr->prec == NULL){
                    if(tmpPtr->count < corrPtr->count){
                        /*POSIZIONA corrPtr dietro tmpPtr e in testa alla lista*/
                        corrPtr->next = tmpPtr;
                        tmpPtr->prec = corrPtr;
                        corrPtr->prec = NULL;
                        *lst = corrPtr;
                        
                    }else{
                        /*ALTRIMENTI POSIZIONALO DAVANTI A tmpPtr*/
                        corrPtr->next = tmpPtr->next;
                        tmpPtr->next = corrPtr;
                        corrPtr->prec = tmpPtr;
                    }
                }   
                else{
                    if(tmpPtr->count < corrPtr->count){
                        /*POSIZIONA corrPtr dietro tmpPtr */
                        tmpPtr->prec->next = corrPtr;
                        corrPtr->prec = tmpPtr->prec;
                        corrPtr->next = tmpPtr;
                        tmpPtr->prec = corrPtr;
                    }
                    else{
                    /*POSIZIONA corrPtr davanti a tmpPtr*/
                    corrPtr->next = tmpPtr->next;
                    tmpPtr->next = corrPtr;
                    corrPtr->prec = tmpPtr;

                    }

                }
            }
            return 1;
        }
        else{
            corrPtr = corrPtr->next;
            pos++;
        }
    }
    puts("-1");

    return -1;
}

void free_lst(List* lst){
    if(lst != NULL && *lst != NULL){
        if((*lst)->next != NULL)
            free_lst(&(*lst)->next);
    
    (*lst)->prec = NULL;
    free(*lst);
    *lst = NULL;
    }
}

void mem_err(){
    puts("memoria heap esaurita.");
    exit(EXIT_FAILURE);
}

Node* sec_alloc_node(){

    Node *tmp = calloc(1, sizeof(Node));

    if(tmp == NULL)
        mem_err();

    return tmp;
}

void print_lst(List lst){
    while(lst != NULL){
        printf("%d, count: %d\n", lst->val, lst->count);
        lst = lst->next;
    }
}
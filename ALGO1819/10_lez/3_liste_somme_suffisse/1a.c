#include <stdio.h>
#include <stdlib.h>

typedef struct node{
    int val;
    struct node* next;
}Node;

typedef Node* List;

void mem_err();
void err();
int  get_int();

Node* insert_tail(List* lst_ptr, int val);

int  suffix_sum(List lst);

void apply_lst(List* lst_ptr);
void print_lst(List lst);
void free_lst(List* lst_ptr);

int main(){

    /*ACQUISISCI n E POI n INTERI, INSERENDOLI IN CODA AD UNA LISTA*/
    int n = get_int();

    List lst = NULL;
    Node* tail = insert_tail(&lst, get_int());

    int i;
    for(i = 0; i < n - 1; i++)
        tail = insert_tail(&tail, get_int());
    
    /*PRINT LIST BEFORE APPLYING CHANGES*/
    print_lst(lst);

    /*PER OGNI ELEMENTO NELLA LISTA*/
        /*CALCOLA SOMMA DEI SUCCESSIVI (0 SE NULL)*/
        /*SOSTITUISCI VALORE ELEMENTO CON SOMMA SUFFISSA*/
    apply_lst(&lst);
    /*PRINT LIST AFTER MODIFICATION*/
    print_lst(lst);
    /*FREE DELLA LISTA*/
    free_lst(&lst);

    return 0;
}

void mem_err(){
    puts("memoria heap esaurita.");
    exit(EXIT_FAILURE);
}
void err(){
    puts("errore generico.");
    exit(EXIT_FAILURE);
}
int  get_int(){
    
    int tmp;
    
    scanf("%d", &tmp);
    scanf("%*[^\n]");
    scanf("%*c");
    
    return tmp;
}

Node* insert_tail(List* lst_ptr, int val){
    if (lst_ptr != NULL){
        /*CREATE NEW NODE*/
        Node* newNode = calloc(1, sizeof(Node));
        if(newNode == NULL)
            mem_err();
        
        newNode->val = val;
        
        if (*lst_ptr == NULL)
            *lst_ptr = newNode;
        else
            (*lst_ptr)->next = newNode;


        return newNode;
        
    }
    err();
    return NULL;
}

int suffix_sum(List lst){
    int temp = 0;
    while(lst != NULL){
        temp += lst->val;
        lst = lst->next;
    }
    return temp;
}

void apply_lst(List* lst_ptr){
    /*PER OGNI EL DELLA LISTA*/
        /*CALCOLA SOMMA SUCCESSIVI*/
        /*SOSTITUISCI AL VALORE CORRENTE*/

    Node* ptr = *lst_ptr;

    while(ptr != NULL){
        ptr->val = suffix_sum(ptr->next);
        ptr = ptr->next;
    }    
}

void print_lst(List lst){
    while(lst != NULL){
        printf("%d ", lst->val);
        lst = lst->next;
    }
    puts("");
}

void free_lst(List* lst_ptr){
    if(lst_ptr != NULL){
        if (*lst_ptr != NULL){
            if((*lst_ptr)->next != NULL)
                free_lst(&((*lst_ptr)->next));
            
            free(*lst_ptr);
            *lst_ptr = NULL;
        }
        lst_ptr = NULL;
    }

}
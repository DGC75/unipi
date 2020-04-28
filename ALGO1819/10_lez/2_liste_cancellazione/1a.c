#include <stdio.h>
#include <stdlib.h>


typedef struct node{
    int val;
    struct node* next;
} Node;

typedef Node* List;

void err();
void mem_err();
int get_int();

int  lst_avg(List lst);
List insert_tail(List* lst_ptr, int val);

void print_lst(List lst);
void filter(List *lst, int val);

void free_lst(List* lst_ptr);

int main(){
    /*ACQUISISCI N, E POI N INTERI METTENDOLI IN CODA AD UNA LISTA*/
    int n = get_int();

    List    lst  = NULL;
    Node*   tail = insert_tail(&lst, get_int());
    int i;
    for(i = 0; i < n - 1; i++)
        tail = insert_tail(&tail, get_int());

    /*CALCOLA E STAMPA AVG*/
    int avg = lst_avg(lst);
    printf("%d\n", avg);
    /*STAMPA LISTA PRIMA DI MODIFICARLA*/
    print_lst(lst);
    /*ELIMINA ELS <= AD AVG*/
    filter(&lst, avg);
    /*STAMPA DI NUOVO LISTA*/

    print_lst(lst);
    /*FREE LIST*/
    free_lst(&lst);


    return 0;
}

void mem_err(){
    puts("memoria heap esaurita.");
    exit(EXIT_FAILURE);
}

int get_int(){
    
    int tmp;
    scanf("%d", &tmp);
    scanf("%*[^\n]");
    scanf("%*c");

    return tmp;
}

int  lst_avg(List lst){
    
    int length = 0, sum = 0;
    while(lst != NULL){
        sum += lst->val;
        length++;
        lst = lst->next;
    }

    return sum/length;
}


List insert_tail(List* lst_ptr, int val){
    if (lst_ptr != NULL){

        /*CREATE NODE*/
            Node* new_node = calloc(1, sizeof(Node));
            if(new_node == NULL)
                mem_err();
            
            new_node->val = val;

        if(*lst_ptr != NULL)
            (*lst_ptr)->next = new_node;
        else
            *lst_ptr = new_node;

        return new_node;
    }
    err();
}

void print_lst(List lst){
    while(lst != NULL){
        printf("%d ", lst->val);
        lst = lst->next;
    }
    puts("");
}
void filter(List *lst, int val){
    
    Node* prec = NULL;
    Node* corr = *lst;

    while(corr != NULL){

        if(corr->val <= val){
            
            Node *tmp;

            if(prec != NULL){
                tmp = corr;
                prec->next = corr->next;
                corr = corr->next;

            }
            else{
                tmp = (*lst);
                (*lst) = (*lst)->next;
                prec = NULL;
                corr = corr->next;
            }

            free(tmp);
            tmp = NULL;
        }
        else{
            prec = corr;
            corr = corr->next;
        }

    }
}

void free_lst(List* lst_ptr){
    if(lst_ptr != NULL){
        if(*lst_ptr != NULL){
            if((*lst_ptr)->next != NULL)
                free_lst( &((*lst_ptr)->next));

            free(*lst_ptr);
            *lst_ptr = NULL;
        }
        lst_ptr = NULL;
    }
}

void err(){
    puts("errore generico.");
    exit(EXIT_FAILURE);
}
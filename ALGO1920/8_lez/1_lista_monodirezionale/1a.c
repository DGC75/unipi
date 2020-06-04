#include <stdio.h>
#include <stdlib.h>


typedef struct node{
    int val;
    struct node* next;
} Node;

typedef Node* NodeList;

Node*  insert_tail_node(FILE *fPtr, Node** last_node);

int     get_int(FILE *fPtr);
void    mem_err();

void    print_list_rev(NodeList head);


int main(){
    /*LEGGE n*/
    int N;
    scanf("%d", &N);
    /*PULIZIA BUFFER*/
    scanf("%*[^\n]");
    scanf("%*c");
    /*PER OGNI INTERO*/

    NodeList head = NULL;
    Node *last_node = NULL;
    
    last_node = insert_tail_node(stdin, &head); 
    
    int i;
    for(i = 0; i < N - 1; i++)
        /*INSERISCI IN CODA ALLA LISTA*/
        /*MANTIENI PUNTATORE ALL'ULTIMO NODO PER AVERE INSERIMENTO COSTANTE*/
        last_node = insert_tail_node(stdin, &last_node);
     
    /*STAMPA LA LISTA IN ORDINE INVERSO*/ 
    print_list_rev(head);  
}

void print_list_rev(NodeList head){
    
    if(head != NULL){
        if( (head->next) != NULL)
            print_list_rev(head->next); 

        printf("%d\n", head->val);
    }

}

Node* insert_tail_node(FILE *fPtr, Node** last_node){

    Node *newNode = calloc(1, sizeof(Node));
    
    if(newNode == NULL)
        mem_err();
    
    newNode->val = get_int(fPtr);

    if((*last_node) != NULL){
        (*last_node)->next = newNode;
        return newNode;
    }

        *last_node = newNode;
        return newNode;
}

int get_int(FILE *fPtr){
    
    int tmp;
    fscanf(fPtr,"%d", &tmp);
    /*CLEAN BUFFER*/
    fscanf(fPtr,"%*[^\n]");
    fscanf(fPtr, "%*c");

    return tmp;
}

void mem_err(){
    puts("memoria heap esaurita");
    exit(EXIT_FAILURE);
}
#include <stdio.h>
#include <stdlib.h>

#define P 99149

typedef struct node{
    int val;
    struct node *next;
} Node;

typedef Node* List;

void insert_el_in_table(int val, List *table_ptr, int* max_ptr, int* conflicts_ptr, int a, int b, int n);

int hash(int x, int a, int b, int n);
int insert_head(List* list_ptr, int* max_ptr, int val); 
void set_max(int *max, List lst);

int list_length(List lst);
void mem_err();
int get_int();



int main(void){
    int n, a, b;
    
    n = get_int();
    a = get_int();
    b = get_int();

    /*ALLOCA TABELLA DI LISTE LUNGA 2n*/
    List table = calloc(2*n, sizeof(Node*));
    if(table == NULL)
        mem_err();
    
    int max_len = 0;
    int conflicts = 0;
    /*METTI n INTERI NELLA TABELLA, USANDO COME INDICE IL VALORE DI HASH DELL'ELEMENTO INSERITO*/
    /*TIENI IL CONTO DEL NUMERO DI CONFLITTI E DELLA LISTA PIU' LUNGA AD OGNI INSERIMENTO*/
    int i;
    for(i = 0; i < n; i++)
        insert_el_in_table(get_int(), &table, &max_len, &conflicts, a , b, n);

    printf("%d\n", max_len);
    printf("%d\n", conflicts);

    return 0;
}



void insert_el_in_table(int val,  List *table_ptr, int* max_ptr, int* conflicts_ptr, int a, int b, int n){
    /*CALCOLA LA HASH DI UN EL. E COLLOCA L'EL IN CIMA ALLA LISTA CON QUELL'INDICE*/
    /*SE LA LISTA != NULL, INCREMENTA CONFLICTS*/
    /*CALCOLA LUNGHEZZA LISTA E SE MAGGIORE DEL VALORE ATTUALE, AGGIORNALA*/
    int index = hash(val, a, b, n);
    *conflicts_ptr += insert_head(&(table_ptr[index]), max_ptr, val); 

}

int insert_head(List* list_ptr, int* max_ptr, int val){
    
    /*CREATE NEW NODE*/
    Node *new_node = calloc(1, sizeof(Node));
    if(new_node == NULL)
        mem_err();

    new_node->val = val; 

    if( *list_ptr == NULL){
        *list_ptr = new_node;
        set_max(max_ptr, list_ptr);
        return 0;
    }
    else{
        new_node->next = list_ptr;
        list_ptr = new_node;
        set_max(max_ptr, *list_ptr);
        return 1;
    }
}

void set_max(int *max, List lst){
    int length = list_length(lst);
    if(length > *max)
        *max = length;
}

int list_length(List lst){
    int length = 0;
    while(lst != NULL){
        length++;
        lst = lst->next;
    }

    return length;
}

int hash(int x, int a, int b, int n){
    return ((a*x + b) % P) % (2*n);
}

int get_int(){

    int temp;
    scanf("%d", &temp);
    scanf("%*[^\n]");
    scanf("%*c");
    return temp;
}

void mem_err(){
    puts("memoria heap esaurita.");
    exit(EXIT_FAILURE);
}
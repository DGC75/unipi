#include <stdio.h>
#include <stdlib.h>

typedef struct node{
    int val;
    struct node *next;
} Node;

typedef Node* List;

void insert_el_in_table(int val, List *table_ptr, int* max_ptr, int* conflicts_ptr);

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
        insert_el_in_table(get_int(), &table, &max_len, &conflicts);

    printf("%d\n", max_len);
    printf("%d\n", conflicts);

    return 0;
}

void insert_el_in_table(int val,  List *table_ptr, int* max_ptr, int* conflicts_ptr){
    
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
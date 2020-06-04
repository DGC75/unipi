#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_STR_LEN 101
#define ELS_NEEDED  15

typedef struct node{
    
    int val_affettivo;
    char *categoria;
    struct node* prec;
    struct node* next;
}Node;

typedef Node* List;
typedef List* Hash_table;

/*Helpers*/
int get_int();
void mem_err();
Hash_table alloc_hash_table(int dim);
void    insert_hash_table(Hash_table* ht_ptr, int dim);
Node*   pop_hash_table(Hash_table* ht_ptr, int dim);
void    print_node(Node* node);
int     hash(char*, int);
int     list_search(List lst, char* str);
Node*   load_new_node(char *str, int val);
void    insert_list(List *lst_ptr, Node* node);
char*   load_string(char *str);
Node*   max_list(List lst);

/*dealloc funcs*/
void free_hash_table(Hash_table *ht_ptr);
void free_node_arr(Node** node_arr, int dim);

void print_lst(List lst){
    while(lst != NULL){
        printf("%s (%d) --> ", lst->categoria, lst->val_affettivo);
        lst = lst->next;
    }
    puts("NULL");
}

void print_ht(Hash_table ht, int dim){
    int i;
    printf("\n\n\nPRINT HASH TABLE\n\n\n");
    for(i = 0; i < dim; i++)
        print_lst(ht[i]);
    
    printf("\n\n---END HASH TABLE--\n\n");
}

int main(){

    int N = get_int();

    Hash_table hash_table = alloc_hash_table(2*N);
    Node* arr[ELS_NEEDED] = {NULL};

    int i;
    for(i = 0; i < N; i++)
        insert_hash_table(&hash_table, 2*N);
    
    /*print_ht(hash_table, 2*N);*/
    /*INSERISCI NELL'ARRAY NELL'ORDINE RICHIESTO E RIMUOVI DALLA TABELLA HASH*/ 
    for(i = 0; i < ELS_NEEDED; i++){
        arr[i] = pop_hash_table(&hash_table, 2*N);
    }
    /*STAMPA NELL'ORDINE RICHIESTO*/
    for(i = 0; i < ELS_NEEDED || arr[i] == NULL; i++){
        print_node(arr[i]);
    }

    /*DEALLOCA STRUTTURE*/
    /*
    free_hash_table(&hash_table);
    free_node_arr(arr, ELS_NEEDED);
    */

}

Node* pop_hash_table(Hash_table* ht_ptr, int dim){
    
    Node *max_node_table = NULL;
    Node *max_node_list  = NULL;
    int max_list_reference = 0;

    /*FIND MAXIMUM NODE IN THE HT*/
    
    int i;
    for(i = 0; i < dim; i++){

        /*SALTA LISTE VUOTE*/
        if((*ht_ptr)[i] == NULL){
            continue;
        }

        max_node_list = max_list((*ht_ptr)[i]);
        if(max_node_table == NULL){
            max_node_table = max_node_list;
            max_list_reference = i;
        }
        else{
            if(max_node_table->val_affettivo <= max_node_list->val_affettivo){
                if(max_node_table->val_affettivo < max_node_list->val_affettivo){
                    max_node_table = max_node_list; 
                    max_list_reference = i;
                }
                else{
                    if(strcmp(max_node_table->categoria, max_node_list->categoria) > 0){
                        max_node_table = max_node_list; 
                        max_list_reference = i;
                    }
                }   
            }
        }
    
    }

    /*printf("EL MASSIMO DELLA TABELLA: %s (%d)\n", max_node_table->categoria, max_node_table->val_affettivo);*/
    /*REMOVE IT FROM HT*/

    if(max_node_table != NULL){
        if(max_node_table->prec != NULL)
            max_node_table->prec->next = max_node_table->next;
        else{
            /*IL NODO E' IN TESTA ALLA LISTA i*/
            (*ht_ptr)[max_list_reference] = max_node_table->next;
        }
    
        if(max_node_table->next != NULL)
            max_node_table->next->prec = max_node_table->prec;
        else{
            /*IL NODO E' IN FONDO ALLA LISTA*/
            if(max_node_table->prec != NULL)
                max_node_table->prec->next = NULL;
        }

    }
    /*RETURN IT*/

    return max_node_table;    
}

Node* max_list(List lst){
    Node *tmp_max = NULL;

    while(lst != NULL){
        if(tmp_max == NULL)
            tmp_max = lst;
        
        if(lst->val_affettivo >= tmp_max->val_affettivo){
            if(lst->val_affettivo > tmp_max->val_affettivo)
                tmp_max = lst;
            else if(strcmp(lst->categoria, tmp_max->categoria) < 0){
                tmp_max = lst;
            }
            
        }
        lst = lst->next;
    }

    return tmp_max;
}

void print_node(Node* node){
    if(node != NULL)
        printf("%s\n", node->categoria);
}

void insert_hash_table(Hash_table *ht_ptr, int dim){
    

    /*LEGGI DA INPUT CATEGORIA E VALORE AFFETTIVO*/
    char str[MAX_STR_LEN + 1] = {'\0'};
    fgets(str, MAX_STR_LEN + 1, stdin);
    
    str[strlen(str) - 1] = '\0';
    int val_affettivo = get_int();
    /*CERCA SE ESISTE GIA' UN NODO CON LA STESSA CATEGORIA*/

    List lst = (*ht_ptr)[hash(str, dim)];
    
    if(list_search(lst, str) == 0){
        /*CREALO E INSERISCILO IN TABELLA*/

        Node* new_node = load_new_node(str, val_affettivo);
        insert_list(&((*ht_ptr)[hash(str, dim)]), new_node);
    }
    else{
        /*AGGIORNALO OPPORTUNAMENTE*/
        while(lst != NULL && (strcmp(str, lst->categoria) != 0)){
            lst = lst->next;
        }
        if(lst->val_affettivo < val_affettivo)
            lst->val_affettivo = val_affettivo;
    }
                
}

void insert_list(List *lst_ptr, Node* node){
    if(lst_ptr == NULL){
        puts("qualcosa e' andato storto...");
        exit(EXIT_FAILURE);
    }
    else{
        if(*lst_ptr == NULL)
            *lst_ptr = node;
        else{
            (*lst_ptr)->prec = node;
            node->next = *lst_ptr;
            *lst_ptr = node;
        }
    }
}

Node* load_new_node(char *str, int val){

    Node* new_node = calloc(1, sizeof(Node));
    if(new_node == NULL)
        mem_err();

    new_node->val_affettivo = val;
    new_node->categoria = load_string(str);

    return new_node;
}

char* load_string(char *str){

    char* new_str = calloc(strlen(str)+1, sizeof(char));
    strcpy(new_str, str);

    return new_str;
}

int list_search(List lst, char* str){

    while(lst != NULL){
        if(strcmp(lst->categoria, str) == 0)
            return 1;
        lst = lst->next;
    }

    return 0;
}

Hash_table alloc_hash_table(int dim){

    Hash_table new_ht = calloc(dim, sizeof(List));

    if(new_ht == NULL)
        mem_err();

    return new_ht;
}

int hash(char* str, int mod){
    unsigned int tmp = 0;

    int i;
    for(i = 0; i < strlen(str); i++)
        tmp += (unsigned int)str[i];
    
    return tmp%mod;
}

int get_int(){
    int tmp;
    scanf("%d", &tmp);
    scanf("%*[^\n]");
    scanf("%*c");

    return tmp;
}

void mem_err(){
    puts("memoria heap esaurita");
    exit(EXIT_FAILURE);
}
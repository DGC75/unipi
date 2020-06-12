#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_STR_LEN 101
#define MAX_PHONE_LEN 21

typedef struct node{
    struct node* prec;
    struct node* next;
    char *name;
    char *phone;
} Node;


typedef Node* List;
typedef List* Hash_table;


void    free_hash_table(Hash_table ht_ptr, int dim);
void    print_ht_list(Hash_table ht, int k);
Hash_table alloc_hash_table(int dim);
int hash(char* str, int mod);
int get_int();
void mem_err();
Node* load_new_node(char* str, char* str_phone);
void insert_list(List *lst_ptr, Node* node);
void insert_hash_table(Hash_table *ht_ptr, int dim);
void free_list(List *lst_ptr);


void print_table(Hash_table ht, int dim){
    int i;
    for(i = 0; i < dim; i++){
        printf("i=%d\n", i);
        print_ht_list(ht, i);
        printf("\n\n");
    }
    
}

int main(){
    /*LEGGI N*/
    int N = get_int();

    Hash_table hash_table = alloc_hash_table(2*N);
    
    int i;
    for(i = 0; i < N; i++){
        insert_hash_table(&hash_table, 2*N);
    }
    

    /*LEGGI K*/
    int K = get_int();

    /*STAMPA LA K-esima LISTA DELLA TABELLA*/
    print_ht_list(hash_table, K);


    /*DEALLOCA HASH TABLE*/
    free_hash_table(hash_table, 2*N);
    return 0;
}


void free_hash_table(Hash_table ht_ptr, int dim){
    
    int i;
    for(i = 0; i < dim; i++){
        if(ht_ptr[i] != NULL){
            free_list((&((ht_ptr)[i])));
        }
    }
    
    free(ht_ptr);
}

void free_list(List *lst_ptr){
    
    if(lst_ptr != NULL){
        
        if((*lst_ptr) != NULL){
            if((*lst_ptr)->next != NULL){
                free_list(&((*lst_ptr)->next));
            }
            free((*lst_ptr)->name);
            free((*lst_ptr)->phone);
            free(*lst_ptr);
            *lst_ptr = NULL;
        }

    }
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

Node* load_new_node(char *str, char* str_phone){
    
    int name_len = strlen(str)+1;
    int phone_len = strlen(str_phone) + 1;

    char* name  = calloc(name_len, sizeof(char));
    char* phone = calloc(phone_len, sizeof(char));

    if(name == NULL || phone == NULL)
        mem_err();
    
    strncpy(name,str, name_len);
    strncpy(phone, str_phone, phone_len);

    Node* new_node = calloc(1, sizeof(Node));

    if(new_node == NULL)
        mem_err();

    new_node->name = name;
    new_node->phone = phone;

    return new_node;
}

void insert_list(List *lst_ptr, Node* node){
    if(*lst_ptr == NULL)
        *lst_ptr = node;
    else{
        List* head = lst_ptr;
        /*SCORRI FINO A QUANDO NON TROVI L'ULTIMO EL. OPPURE*/
        /*UN ELEMENTO LESSIC.MENTE MAGGIORE*/
        while( ((*lst_ptr)->next != NULL)  && (strcmp(node->name, (*lst_ptr)->name) > 0)){
            lst_ptr = &((*lst_ptr)->next);
        }


        /*SE SONO ALL'ULTIMO EL., DEVO CONTROLLARE SE METTERLO PRIMA O DOPO*/
        if(((*lst_ptr)->next == NULL)){

            if(strcmp(node->name, (*lst_ptr)->name) < 0){
                /*METTILO PRIMA*/

                /*Il *lst_ptr non punta al primo elemento della lista*/
                if((*lst_ptr)->prec != NULL){
                    
                    node->prec = (*lst_ptr)->prec;
                    node->next = (*lst_ptr);
                    node->next->prec = node;
                    node->prec->next = node;
                    
                }
                else{ /* *lst_ptr->prec == NULL*/

                    node->next = (*lst_ptr);
                    (node->next)->prec = node;
                    *head = node;
                     
                }
            
            }
            else{
                /*METTILO DOPO*/
                ((*lst_ptr)->next) = node;
                node->prec = (*lst_ptr);

            }
        }
        else{
            /*NON SONO ALL'ULTIMO NODO*/
            /*IN QUESTO CASO, VA MESSO PRIMA*/

            /*VA MESSO IN TESTA*/
            if((*lst_ptr)->prec == NULL){
                
                node->next = *lst_ptr;
                
                node->next->prec = node;
                *head = node;
            }
            else{
                /*VA MESSO IN MEZZO*/
                
                node->next = (*lst_ptr);
                node->prec = (*lst_ptr)->prec;
                (node->prec)->next = node;
                (node->next)->prec = node;
                
            }

        }
    
    }
}

void insert_hash_table(Hash_table *ht_ptr, int dim){
    

    /*LEGGI DA INPUT NOME E TELEFONO*/
    char str[MAX_STR_LEN + 1] = {'\0'};
    fgets(str, MAX_STR_LEN + 1, stdin);
    str[strlen(str) - 1] = '\0';


    char phone[MAX_PHONE_LEN + 1] = {'\0'};
    fgets(phone, MAX_PHONE_LEN +1, stdin);
    phone[strlen(phone) - 1] = '\0';

    /*CREA NODO E INSERISCILO NELLA LISTA APPROPRIATA, ALLA POSIZIONE CORRETTA*/
    
    Node* new_node = load_new_node(str, phone);
    insert_list(&((*ht_ptr)[hash(str, dim)]), new_node);
                
}

void print_ht_list(Hash_table ht, int k){
    
    List lst = (ht[k]);
    if(lst == NULL)
        return;

    while(lst != NULL){
        printf("%s %s\n", lst->name, lst->phone);
        lst = lst->next;
    }

}
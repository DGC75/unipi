#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_STR_LEN 100
#define ELS_NEEDED  15


typedef struct node{
    int val_aff;
    char *category;
    struct node *prec;
    struct node *next;
    int selected;
} Node;

typedef Node* List;

int get_int();
void mem_err();

int hash(char*, int);
void insert_el_in_table(List *table_ptr, int);
int search_node(List, Node*);
Node* pop_max_element(List**, int);
void print_arr(Node**, int dim);
void free_table(List**, int dim);
void free_els_arr(Node**, int dim);

int main(){
    
    /*LEGGI N*/
    int N = get_int();

    /*ALLOCA TABELLA HASH A LISTE DI TRABOCCO*/
    /*DI DIM 2N*/
    List* table = calloc(2*N, sizeof(Node*));

    if(table == NULL)
        mem_err();

    int i;
    for(i = 0; i < N; i++)
        insert_el_in_table(table, 2*N);
    
    puts("Inizio dell'inferno");
    /*ORDINA TABELLA*/
        /*DICHIARA ARRAY E INIZIALIZZALO*/
        Node* arr[ELS_NEEDED] = {NULL};

        /*INSERISCI AL MASSIMO 15 ELEMENTI NELL'ARRAY NELL'ORDINE INDICATO*/
    
        for(i = 0; i < ELS_NEEDED; i++)
            arr[i] = pop_max_element(&table, 2*N);
    

    puts("Sei arrivato alla fine dell'inferno");
    /*STAMPA AL MASSIMO I PRIMI 15 ELEMENTI*/
    print_arr(arr, ELS_NEEDED);

    /*DEALLOCA TABELLA*/
    free_table(&table, 2*N);
    free_els_arr(arr, ELS_NEEDED);

    return 0;
}

void print_arr(Node** arr_ptr, int dim){
    int i;
    for(i = 0; i < dim; i++){
        if(arr_ptr[i]== NULL)
            return;
        
        printf("%s\t\t%d\n", arr_ptr[i]->category, arr_ptr[i]->val_aff);
    }
}
void free_table(List** table_ptr, int dim){

}
void free_els_arr(Node** arr_ptr, int dim){

}


Node* pop_max_element(List** table_ptr, int dim){
    /*TROVA L'ELEMENTO COL MASSIMO VALORE AFFETTIVO*/
    /*E COL MINIMO VALORE LESSICOGRAFICO*/
    Node *current_max = NULL;
    Node *tmp_max = NULL;
    Node** max_selected_list = NULL;
    Node** max_selected_table = NULL;

    /*GUARDO IN OGNI LISTA*/
    int i;
    for(i = 0; i < dim; i++){
        
        max_selected_list = NULL;

        if((*table_ptr)[i] != NULL){
            
            List* lst = &((*table_ptr)[i]);

            Node* max = NULL;
            
            /*SE LA LISTA E' VUOTA, SALTO ALLA PROSSIMA LISTA*/
            if(lst == NULL || *lst == NULL)
                continue;
            
            if((*lst)->selected == 0)
                max = (*lst);

            /*FINCHE' NON SONO ALL'ULTIMO NODO*/
                     

            while(lst != NULL && *lst != NULL && (*lst)->next != NULL){
            
                while(max == NULL && (*lst)->next != NULL){
                    if((*lst)->selected == 0){
                        max = (*lst);
                        break;
                    }
                    else if(max == NULL)
                        lst = &((*lst)->next);

                    puts("here foverever");
                }

                if( ((*lst)->selected == 0) && (max->val_aff <= (*lst)->val_aff) ){
                    if(max->val_aff < (*lst)->val_aff){
                        max = (*lst);
                        max_selected_list = lst;
                    }
                    else{
                        if(strcmp(max->category, (*lst)->category) < 0){
                            max = *lst;
                            max_selected_list = lst;
                        }
                    }

                }


                lst = &((*lst)->next);

            }


            /*DEVO GUARDARE L'ULTIMO NODO*/
            if(lst != NULL && *lst != NULL && max->val_aff <= (*lst)->val_aff && (*lst)->selected == 0){

                if(max->val_aff < (*lst)->val_aff){
                    max = (*lst);
                    max_selected_list = lst;
                    }
                else{
                    if(strcmp(max->category, (*lst)->category) < 0){
                        max = *lst;
                        max_selected_list = lst;
                    }
                }

            }
            
            if(*max_selected_list != NULL){
                printf("trovato il massimo della lista[%d]: %d %s\n", i,  (*max_selected_list)->val_aff, (*max_selected_list)->category);

            }
            else{
                puts("LISTA 'VUOTA'");
                exit(EXIT_FAILURE);
            }
            /*adesso max_selected_list punta al puntatore del nodo massimo dell'iesima lista*/
            /*max adesso punta al nodo massimo dell'iesima lista*/
            
            tmp_max = max;
            max = NULL;
            /*adesso guardo se l'attuale massimo selezionato e' minore del massimo trovato*/
            if(current_max != NULL && tmp_max != NULL && tmp_max->val_aff >= current_max->val_aff){
                

                if(tmp_max->val_aff > current_max->val_aff){
                    current_max = tmp_max;
                    if(max_selected_list != NULL)
                        max_selected_table = max_selected_list;
                }
                else if(current_max != NULL && tmp_max != NULL)
                    if(strcmp(tmp_max->category, current_max->category) < 0){
                        current_max = tmp_max;
                    if(max_selected_list != NULL)
                        max_selected_table = max_selected_list;
                    }
            }

            if(current_max == NULL && tmp_max != NULL){
                current_max = tmp_max;
                max_selected_table = max_selected_list;
            }

            if(current_max != NULL)
                printf("massimo aggiornato della lista %d: %s con valore %d\n",i ,current_max->category, current_max->val_aff);
            else
                printf("la lista %d e' vuota\n", i);
        }
    }   

    printf("QUI\n");

    if(max_selected_table == NULL)
        puts("QUALCOSA E' ANDATO STORTO");

    /*max_selected_table SAREBBE UNA SORTA DI 'CANCELLAZIONE LOGICA' DALLA MEMORIA*/
    if(max_selected_table != NULL && *max_selected_table != NULL)
        (*max_selected_table)->selected = 1;

    max_selected_table = NULL;
    if(current_max != NULL)
        printf("massimo trovato nella tabella: %s con valore %d\n", current_max->category, current_max->val_aff);
    
    return current_max;
}


void insert_el_in_table(List *table_ptr, int mod){
    
    char str[MAX_STR_LEN + 1] = {'\0'};
    fgets(str,MAX_STR_LEN + 1, stdin);

    int len = strlen(str);
    str[len-1] = '\0';
    len -= 1;
    int tmp_val_aff = get_int();

    printf("stringa acquisita: '%s'\n", str);
    printf("lunghezza stringa: %d\n", len);
    int hash_val = hash(str, mod);
    printf("hash: %d\n", hash_val);
    Node* new_node = calloc(1, sizeof(Node));

    if(new_node == NULL)
        mem_err();

    new_node->category = calloc(len+1, sizeof(char));

    if(new_node->category == NULL)
        mem_err();  

    strcpy(new_node->category, str);
    new_node->val_aff = tmp_val_aff;
    
    List *lst = &(table_ptr[hash_val]);
   
    /*SE LA LISTA E' VUOTA O NON CONTIENE UN ELEMENTO CON QUEL NOME, INSERISCI IN TESTA*/
    if((*lst) == NULL || search_node(*lst, new_node) == 0){
        new_node->next = *lst;
        
        *lst = new_node;

        return;
    }
    else{
        /*CERCA L'ELEMENTO CHE HA LO STESSO NOME*/
        Node* search_ptr = *lst;
        while(search_ptr != NULL){
            if(strcmp(search_ptr->category, new_node->category) != 0)
                search_ptr = search_ptr->next;
            else{
                /*HO TROVATO UN ELEMENTO CON LO STESSO NOME*/
                if(search_ptr->val_aff < new_node->val_aff)
                    search_ptr->val_aff = new_node->val_aff;
                break;
            }
        }

        /*QUI C'ERA UNA FREE NODE*/
        free(new_node);
        new_node = NULL;
    }
}

int search_node(List list, Node* node){
Node* search_ptr = list;
        while(search_ptr != NULL){
            if(strcmp(search_ptr->category, node->category) != 0)
                search_ptr = search_ptr->next;
            else
                return 1;
        }
        return 0;    
}

int hash(char* str, int mod){
    int tmp = 0;

    int i;
    for(i = 0; i < strlen(str); i++)
        tmp += str[i];
    
    return tmp%mod;
}

void mem_err(){
    puts("memoria heap esaurita.");
    exit(EXIT_FAILURE);
}

int get_int(){

    int temp;
    scanf("%d", &temp);
    scanf("%*[^\n]");
    scanf("%*c");
    return temp;
}
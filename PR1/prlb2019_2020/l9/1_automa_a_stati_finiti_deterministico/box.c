#include <stdio.h>
#include <stdlib.h>
#include <string.h>


#define MAX_STR 100

typedef struct transizione{
    
    char acceptable_char;
    char* next_state;
    
    struct transizione* next;
    
}Transizione;

typedef Transizione* Lista_Transizioni;

typedef struct stato{
    
    char *nome_stato;
    Lista_Transizioni lst_trans_stato;
    
    struct stato* next;
            
}Stato;

typedef Stato* Lista_stati;

typedef struct automa{
    
    int n_stati;
    Lista_stati lst_stati;
        
}Automa;

void acquisisci_automa(Automa **aPtr);
int  str_belong(char * str, Automa *aPtr);
char* get_new_state(char c, char* current_state, Lista_stati lPtr);
void insert(Lista_Transizioni *lPtr, Transizione **trans);
void insert_state(Lista_stati *lsPtr, Stato **sPtr);

void cleanBuffer(char *str, int dim);
void mem_error();
void save_int(int* val);
void errore_input();

int main(){
    
    Automa* automa = NULL;
    
    acquisisci_automa(&automa);
    
    char riga[MAX_STR +1];
    
    fgets(riga, MAX_STR+1, stdin);
    riga[strlen(riga)-1] = '\0';
    
    while( (strcmp(riga, "FINE") != 0) ){
        
        if(str_belong(riga, automa)){

            printf("%s\n", riga);
        }
        fgets(riga, MAX_STR+1, stdin);
        riga[strlen(riga)-1] = '\0';
    }
    
    return 0;
}

void acquisisci_automa(Automa **aPtr){
    
    int n_stati;
    int i;
    
    Automa *newAutoma = calloc(1, sizeof(Automa));
    if(newAutoma == NULL)
        mem_error();
        
    save_int(&n_stati);
    char string[MAX_STR] = {'\0'};
    
    Stato *newStato = NULL;

    for(i = 0; i < n_stati; ++i){
        
        
        scanf("%[^;]", string);

        newStato = calloc(1, sizeof(Stato));
        newStato->nome_stato = calloc(strlen(string)+1, sizeof(char));
        strcpy(newStato->nome_stato, string);
        
        
        cleanBuffer(string, MAX_STR);
        static char tmp_c;
        
        
        while(scanf(";(%[^,],%c)", string, &tmp_c) == 2){
            
            Transizione *newTrans = calloc(1, sizeof(Transizione));
            newTrans->acceptable_char = tmp_c;
            newTrans->next_state = calloc( strlen(string) + 1, sizeof(char));
            strcpy(newTrans->next_state, string);
            
            insert(&(newStato->lst_trans_stato), &newTrans);
                                
        }
        
        insert_state(&(newAutoma->lst_stati), &(newStato));
        
        scanf("%*c");   
    }
        
    *aPtr = newAutoma;
}


void insert_state(Lista_stati *lsPtr, Stato **sPtr){
    
    if(*lsPtr == NULL){
        *lsPtr = *sPtr;
    }
    else{
        while((*lsPtr)->next != NULL){
            lsPtr = &(*lsPtr)->next;
        }
        (*lsPtr)->next = *sPtr;
        
    }
    
}

void insert(Lista_Transizioni *lPtr, Transizione **trans){
    
    if(*lPtr == NULL){
        *lPtr = *trans;
    }
    else{
        while((*lPtr)->next != NULL){
            lPtr = &(*lPtr)->next; 
        }
        (*lPtr)->next = *trans;
    }
    
}


void cleanBuffer(char *str, int dim){
    int i;
    for(i = 0; i < dim; ++i){
        str[i] = '\0';
    }
}


int str_belong(char * str, Automa *aPtr){
    
    int str_size = strlen(str);
    int i;
    
    
    
    char *curr_state = aPtr->lst_stati->nome_stato;
    
                   

    for(i = 0; i < str_size; ++i){

        curr_state = get_new_state(str[i], curr_state, aPtr->lst_stati);    
        if(curr_state[0] == '\0'){
            return 0;
        }        
    }
    
    if(curr_state[0] == 'F')
        return 1;
    else
        return 0;
}

char* get_new_state(char c, char* curr_state, Lista_stati lPtr){
    while(lPtr != NULL){
        
        if(strcmp(lPtr->nome_stato, curr_state) == 0){
            Transizione* tPtr = lPtr->lst_trans_stato;
            while(tPtr != NULL){
                
                if(c == tPtr->acceptable_char)
                    return tPtr->next_state;
                
                tPtr = tPtr->next;
            }
        }
        
        lPtr = lPtr->next;
    }
    
    return "";
}

void save_int(int *val){
    if(scanf("%d", val) != 1 || *val < 1 )
        errore_input();
    
    scanf("%*c");    
}

void mem_error(){
    puts("Memoria esaurita");
    exit(EXIT_FAILURE);
}

void errore_input(){
    puts("Errore nell'input");
    exit(EXIT_FAILURE);
}


#include <stdio.h>
#include <stdlib.h>

typedef struct transizione{

    char accepted_c;
    int next_state;
    
    struct transizione* next;
    
}Transizione;

typedef Transizione* ListaTransizioni;

typedef struct automa{

    ListaTransizioni* arr_lst_trans;
    int *arr_stati_finali;
    
} Automa;

int acquisisci_automa(Automa** aPtr);
int  riconosci_str(Automa* aPtr, char *str, int dim);
void insert(ListaTransizioni *lPtr, int next_state, char accepted_c);
int find_in_list(Automa *aPtr, int state, char c);
int is_in(int val, int *arr, int dim);


void saveInt(int *val);
void errore_input();
void mem_error();


int main(){

    Automa *automa = NULL;    
    int dim = acquisisci_automa(&automa);

    char line[101];
    scanf("%[^\n]", line);
    printf("'%s'\n", line);
    if(riconosci_str(automa, line, dim))
        puts("Stringa appartenente al linguaggio.");
    else
        puts("Stringa non appartenente al linguaggio.");
        
        
    return 0;
}

int acquisisci_automa(Automa** aPtr){

    Automa *newAutoma = calloc(1, sizeof(Automa));
    int n_states, n_final_states;
    
    saveInt(&n_states);
    saveInt(&n_final_states);

    newAutoma->arr_lst_trans = calloc(n_states,sizeof(ListaTransizioni));
    newAutoma->arr_stati_finali = calloc(n_final_states, sizeof(int));
    
    int i, tmp;
    for(i = 0; i < n_final_states; ++i){
       scanf("%d", &tmp);
       newAutoma->arr_stati_finali[i] = tmp;
    }
    int next_state;
    char accepted_c;
    for(i = 0; i < n_states; ++i){
        
        scanf("%*d");
        while(scanf(";(%d,%c)", &next_state, &accepted_c) == 2){
            insert(&(newAutoma->arr_lst_trans[i]), next_state, accepted_c);
        }
        
    }

    return n_final_states;
}


int  riconosci_str(Automa* aPtr, char *str, int dim){
    int i = 0;

    int curr_state = 0;
    char c = str[i];
    for(i = 1; c!='\0' && c!='\n'; ++i){
        
        curr_state = find_in_list(aPtr, curr_state, c);
        c = str[i];
    }

    return is_in(curr_state, aPtr->arr_stati_finali, dim);
}

int find_in_list(Automa *aPtr, int state, char c){
    return 1;
}

int is_in(int val, int *arr, int dim){
    return 1;
}

void insert(ListaTransizioni *lPtr, int next_state, char accepted_c){

    Transizione *newTrans = calloc(1, sizeof(Transizione));

    if (newTrans == NULL)
        mem_error();

    newTrans->next = *lPtr;
    (*lPtr) = newTrans;
}




void saveInt(int *val){
    if(scanf("%d", val) != 1 || *val < 0 )
        errore_input();
}

void errore_input(){
    puts("Errore input");
    exit(EXIT_FAILURE);
}

void mem_error(){
    puts("Memoria esaurita");
    exit(EXIT_FAILURE);
}
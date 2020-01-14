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

void acquisisci_automa(Automa** aPtr);
int  riconosci_str(Automa* aPtr, char *str);
void insert(ListaTransizioni *lPtr, int next_state, char accepted_c);
void saveInt(int *val);
void errore_input();

int main(){

    Automa *automa = NULL;    
    acquisisci_automa(&automa);
    
    char line[101];
    fgets(line, 101, stdin);
    
    if(riconosci_str(automa, line))
        puts("Stringa appartenente al linguaggio.");
    else
        puts("Stringa non appartenente al linguaggio.");
        
        
    return 0;
}

void acquisisci_automa(Automa** aPtr){

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
}


int  riconosci_str(Automa* aPtr, char *str){
    return 1;
}

void insert(ListaTransizioni *lPtr, int next_state, char accepted_c){
    
}

void saveInt(int *val){
    if(scanf("%d", val) != 1 || *val < 0 )
        errore_input();
}

void errore_input(){
    puts("Errore input");
    exit(EXIT_FAILURE);
}

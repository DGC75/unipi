#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_DIM 100

typedef enum bool{
	false = 0,
	true  = 1
}Bool;

typedef struct transizione{

	char *next_state;
	char acceptable_char;
	struct transizione* next_trans;

}Transizione;

typedef Transizione* ListaTransizioni;

typedef struct stato{
	char *nome;
	ListaTransizioni lista_transizioni;
}Stato;

void errore_input(void);
void mem_error(void);

void salva_int(int *input);
int lunghezza_stringa(FILE* file_input);
void aggiungi_nuovo_stato(Stato* stati_automa);
void insert_ListaTransizioni(ListaTransizioni *lPtr, Transizione* newTrans);
Bool string_belong(char *str, int dim, Stato *stati_automa);
Bool is_there(char c, ListaTransizioni lPtr);
void set_current_state(char** c, ListaTransizioni lPtr);

int main(void){

	int i, n_stati;
	salva_int(&n_stati);

	Stato stati_automa[n_stati];

	for (i = 0; i < n_stati; ++i){
		aggiungi_nuovo_stato(&stati_automa[i]);	
	}

	char riga[MAX_DIM];
	while(fgets(riga, MAX_DIM, stdin) != NULL && (strcmp(riga,"FINE") != 0)){
		if (string_belong(riga, MAX_DIM, stati_automa)){
			printf("%s\n", riga);
		}
	}	
}

void aggiungi_nuovo_stato(Stato* stato_automa){

	static int str_len;
	static char *token;

	str_len = lunghezza_stringa(stdin);
	char riga[str_len];
	fgets(riga, str_len+1, stdin);
	riga[str_len-1] = '\0';
	printf("riga: '%s'\n", riga);
	token = strtok(riga, ";(,)");

	if (token != NULL){

		stato_automa = calloc(1, sizeof(Stato));

		if (stato_automa == NULL){
			mem_error();
		}
			
		stato_automa->nome = token;
		printf("%s\n", stato_automa->nome);
		token = strtok(NULL, ";(,)");
			
		while(token != NULL){

			Transizione* newtrans = calloc(1, sizeof(Transizione));

			if (newtrans == NULL){
				mem_error();
			}
			else{
				newtrans->next_state = token;

				token = strtok(NULL, ";(,)");
				newtrans->acceptable_char = *token;

				/*INSERISCO LA TRANSIZIONE NELLA LISTA*/
				insert_ListaTransizioni(&stato_automa->lista_transizioni, newtrans);
				token = strtok(NULL, ";(,)");
			}
		}
	}

}

Bool string_belong(char *str,int dim, Stato *stati_automa){
	
	int i;
	static char c;
	char *current_state = stati_automa[0].nome;

	for (i = 0; i < dim; ++i){
		c = str[i];
		if (is_there(c, stati_automa->lista_transizioni)){
			set_current_state(&current_state, stati_automa->lista_transizioni);
		}
		else{
			return false;
		}
	}
	if ( current_state[0] == 'F' ) {
		return true;
	}
	else{
		return false;
	}
}

Bool is_there(char c, ListaTransizioni lPtr){

}

void set_current_state(char** c, ListaTransizioni lPtr){

}

void insert_ListaTransizioni(ListaTransizioni *lPtr, Transizione* newTrans){
	if (*lPtr == NULL){
		*lPtr = newTrans;
	}
	else{
		ListaTransizioni tmpPtr = (*lPtr);
		*lPtr = newTrans;
		newTrans->next_trans = tmpPtr;

	}
}

void mem_error(void){
	puts("memoria esaurita.");
	exit(EXIT_FAILURE);
}

int lunghezza_stringa(FILE* file_input){

	int result = 0;

	fpos_t  start_pos;
	fgetpos(stdin, &start_pos);

	char c = fgetc(stdin);
	while(c != '\n' && c != EOF){
		++result;
		c = fgetc(stdin);
	}
	fsetpos(stdin, &start_pos);
	return result+1;
}

void salva_int(int *input){
	if (scanf("%d", input) != 1 || *input < 1){
		errore_input();
	}
	scanf("%*c");
}

void errore_input(void){
	puts("input non corretto");
	exit(EXIT_FAILURE);
}

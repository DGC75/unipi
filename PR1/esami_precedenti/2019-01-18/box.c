#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define LST_END (memcmp("xxx", (newStud)->cognome, 3) == 0) && (memcmp("xxx", (newStud)->nome,3) == 0) && (newStud->voto == -1)
#define INPUT_NOT_CORRECT (newStud)->voto <0 || (newStud)->voto > 30 

typedef struct studente{
	char cognome[21];
	char nome[21];
	int voto;
}Studente;

typedef Studente* ListaStudenti;

void acquisisci_stud(Studente* stud);
void aggiungi_stud_alf(ListaStudenti *lPtr, Studente*newStud);
int  is_there(ListaStudenti lPtr, Studente* newStud);
void delete(ListaStudenti *lPtr, Studente* newStud);
void stampa_elenco(ListaStudenti lPtr, char *cognome);

int main(){

	ListaStudenti lst_compitino = NULL;
	Studente *newStud = calloc(1, sizeof(Studente));
	char cognome[21] = {'\0'};
	
	if(newStud == NULL){
		puts("Memoria esaurita");
		exit(EXIT_FAILURE);
	}
	acquisisci_stud(newStud);
	while(!(LST_END)){
		aggiungi_stud_alf(&lst_compitino, newStud);
		acquisisci_stud(newStud);
	}

	acquisisci_stud(newStud);
	while(!(LST_END)){
		if(is_there(lst_compitino, newStud))
			delete(&lst_compitino, newStud);
			
		acquisisci_stud(newStud);
	}	
	fgets(cognome,21,stdin);
	stampa_elenco(lst_compitino, cognome);
	return 0;
}

void acquisisci_stud(Studente* newStud){
	if(scanf("%[a-z-A-Z];%[a-z-A-Z];%d", (newStud)->cognome, (newStud)->nome, &(newStud)->voto)!=3 || (INPUT_NOT_CORRECT) ){
		if(!(LST_END)){
			puts("Errore nell’input.");
			exit(EXIT_FAILURE);
		}
	}
	scanf("%*c");
}

void aggiungi_stud_alf(ListaStudenti *lPtr, Studente*newStud){
	
}

int  is_there(ListaStudenti lPtr, Studente* newStud){
	return 1;
}

void delete(ListaStudenti *lPtr, Studente* newStud){

}

void stampa_elenco(ListaStudenti lPtr, char *cognome){

}

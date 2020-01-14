#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define LST_END (memcmp("xxx", (newStud)->cognome, 3) == 0) && (memcmp("xxx", (newStud)->nome,3) == 0) && ((newStud)->voto == -1)
#define LST_END_2 (memcmp("xxx", (*newStud)->cognome, 3) == 0) && (memcmp("xxx", (*newStud)->nome,3) == 0) && ((*newStud)->voto == -1)
#define INPUT_NOT_CORRECT (*newStud)->voto <0 || (*newStud)->voto > 30 
#define DIFFERENT_STUDENTS strcmp(corrPtr->cognome, newStud->cognome) != 0 || strcmp(corrPtr->nome, newStud->nome) != 0 || (corrPtr->voto) != (newStud->voto)
#define DIFFERENT_STUDENTS_2 strcmp( (*lPtr)->cognome, newStud->cognome) != 0 || strcmp((*lPtr)->nome, newStud->nome) != 0 || ( (*lPtr)->voto) != (newStud->voto)

typedef struct studente{
	char cognome[21];
	char nome[21];
	int voto;
	struct studente* next;
}Studente;

typedef Studente* ListaStudenti;

void acquisisci_stud	(Studente** stud);
void aggiungi_stud_alf	(ListaStudenti *lPtr, Studente* tmpStud);
void delete				(ListaStudenti *lPtr, Studente* newStud);
void stampa_elenco		(ListaStudenti lPtr, char *cognome);


void print_studente(Studente *stud);
void print_lst(ListaStudenti lPtr);

int main(){

	ListaStudenti lst_compitino = NULL;
	Studente *newStud = calloc(1, sizeof(Studente));
	char cognome[21] = {'\0'};
	
	if(newStud == NULL){
		puts("Memoria esaurita");
		exit(EXIT_FAILURE);
	}
	acquisisci_stud(&newStud);

	while(!(LST_END)){
		aggiungi_stud_alf(&lst_compitino, newStud);
		acquisisci_stud(&newStud);
	}

	acquisisci_stud(&newStud);
	while(!(LST_END)){
		delete(&lst_compitino, newStud);
		acquisisci_stud(&newStud);
	}	

	fgets(cognome,21,stdin);	
	stampa_elenco(lst_compitino, cognome);
	return 0;
}

void acquisisci_stud(Studente** newStud){
	if(scanf("%[a-z-A-Z];%[a-z-A-Z];%d", (*newStud)->cognome, (*newStud)->nome, &(*newStud)->voto)!=3 || (INPUT_NOT_CORRECT) ){
		if(!(LST_END_2)){
			puts("Errore nell'input.");
			exit(EXIT_FAILURE);
		}
	}
	scanf("%*c");
}

void aggiungi_stud_alf(ListaStudenti *lPtr, Studente *tmpStud){

	Studente *newStud = calloc(1, sizeof(Studente));
	memcpy(newStud ,tmpStud, sizeof(Studente));

	if (*lPtr == NULL){
		(*lPtr) = newStud;		
	}
	else{
		Studente *precPtr = NULL;
		Studente *corrPtr = *lPtr;
	
		while(corrPtr!= NULL && memcmp(newStud->cognome, corrPtr->cognome,sizeof((*newStud).cognome))>0){
			precPtr = corrPtr;
			corrPtr = corrPtr->next;
		}

		while(corrPtr!= NULL && (memcmp(newStud->cognome, corrPtr->cognome,sizeof((*newStud).cognome)) == 0)  && memcmp(newStud->nome, corrPtr->nome,sizeof((*newStud).nome))>0){
				precPtr = corrPtr;
				corrPtr = corrPtr->next;
		}			
		if (precPtr == NULL){
			newStud->next = *lPtr;
			*lPtr = newStud;
		}
		else{
			precPtr->next = newStud;
			newStud->next = corrPtr;
		}
	}	
}


void delete(ListaStudenti *lPtr, Studente* newStud){
	if (*lPtr != NULL){
		if (!(DIFFERENT_STUDENTS_2)){
			Studente *tmpPtr = *lPtr;
			*lPtr = (*lPtr)->next;
			free(tmpPtr);
		}
		else{
			Studente *precPtr = *lPtr;
			Studente *corrPtr = (*lPtr)->next;

			while(corrPtr != NULL && (DIFFERENT_STUDENTS) ){
				precPtr = corrPtr;
				corrPtr = corrPtr->next;
			}
			if (corrPtr != NULL){
				Studente *tmpPtr = corrPtr;
				precPtr->next = corrPtr->next;
				free(tmpPtr);
			}
		}
	}
}

void stampa_elenco(ListaStudenti lPtr, char *cognome){
	while(lPtr != NULL){
		if (strcmp(lPtr->cognome, cognome) == 0){
			printf("%20s%20s%20d\n",lPtr->cognome, lPtr->nome,lPtr->voto);
		}
		lPtr = lPtr->next;
	}
}

void print_lst(ListaStudenti lPtr){
	while(lPtr != NULL){
		print_studente(lPtr);
		lPtr = lPtr->next;
	}
}

void print_studente(Studente *stud){
	printf("cognome:%s\tnome:%s\tvoto:%d\n", stud->cognome, stud->nome, stud->voto);
}

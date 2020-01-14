#include <stdio.h>
#include <stdlib.h>
#include <string.h>

struct rappresentante{

	char nome[10];
	int voti;
	struct rappresentante *nextRappr;

};

typedef struct rappresentante Rappresentante;
typedef 	   Rappresentante *RapprPtr;

void insertRappr		(RapprPtr *listPtr,char* nome);
void aggiungiVoto		(RapprPtr *listPtr, char* nome);
int  cercaRappr			(RapprPtr *listPtr, char* nome);
void elaboraNome		(RapprPtr *listPtr, char* nome);
void stampaVincitori	(RapprPtr listPtr);
void stampaLista		(RapprPtr listPtr);
void riordinaLista		(RapprPtr listPtr);

int main(void){

	RapprPtr lista=NULL;

		FILE *fPtr;

		if ((fPtr = fopen("input.txt","r")) == NULL){
			puts("Impossibile aprire file");
			exit(EXIT_FAILURE);

		}else{

			while(!feof(fPtr)){

				char nome1[10];
				char nome2[10];
				fscanf(fPtr,"%[^,],%s\n", nome1, nome2);
				elaboraNome(&lista, nome1);
				elaboraNome(&lista, nome2);

			}
			stampaLista(lista);
			puts("");
			riordinaLista(lista);
			stampaLista(lista);
			stampaVincitori(lista);
		}	
	return 0;
}

void stampaLista(RapprPtr listPtr){

	while(listPtr!=NULL){

		printf("Nome:%s\tVoti:%d\n", listPtr->nome, listPtr->voti);
		listPtr= listPtr->nextRappr;
	}
}

void elaboraNome(RapprPtr *listPtr, char* nome){

	if (cercaRappr(listPtr, nome) == 1){
		aggiungiVoto(listPtr, nome);
	} 
	else{
		insertRappr(listPtr, nome);
	}
}

int cercaRappr(RapprPtr *listPtr, char* nome){

	if (*listPtr == NULL){
		return 0;
	}
	if (strcmp((*listPtr)->nome, nome) == 0){
		return 1;
	}else{
		return cercaRappr(&(*listPtr)->nextRappr, nome);
	}
	return 0;
}

void aggiungiVoto(RapprPtr *listPtr, char* nome){

	if (strcmp((*listPtr)->nome, nome) == 0){
		(*listPtr)->voti+=1;
		return;
	}else{
		aggiungiVoto(&(*listPtr)->nextRappr, nome);
	}
}

void insertRappr(RapprPtr *listPtr, char* nome){

	Rappresentante *newStud = calloc(1, sizeof(Rappresentante));
	newStud->voti=1;
	strcpy(newStud->nome, nome);
	if (newStud!=NULL){
		if (*listPtr != NULL){

			newStud->nextRappr = *listPtr;
			*listPtr = newStud;  
		}else{

			*listPtr = newStud;
		}
	}
	else{
		puts("Memoria esaurita");
		exit(EXIT_FAILURE);
	}

}

void riordinaLista(RapprPtr listPtr){
	/*ORDINA IN ORDINE DI VOTO DECRESCENTE*/
	/*SE DUE VOTI SONO UGUALI, ALLORA ORDINALI IN ORDINE LESSICOGRAFICO*/

	/*CALCOLO QUANTI ELEMENTI CI SONO NELLA LISTA*/
	int length_lista=0;
	RapprPtr cursore = listPtr;
	while(cursore!=NULL){
		length_lista++;
		cursore=cursore->nextRappr;
	}
	/*SELECTION SORT*/
	int i, j;
	RapprPtr maxPtr = listPtr;
	cursore = listPtr->nextRappr;
	for (i = 0; i < length_lista-1; ++i){
		cursore=maxPtr->nextRappr;
		for (j = i+1; j < length_lista; ++j){

			if (cursore->voti > maxPtr->voti){
				/*SWAP THEM*/
				char tempNome[10];
				int tempVoti;

				strcpy(tempNome, cursore->nome);
				tempVoti=cursore->voti;

				strcpy(cursore->nome, maxPtr->nome);
				cursore->voti = maxPtr->voti;

				strcpy(maxPtr->nome, tempNome);
				maxPtr->voti = tempVoti;

			}else if(cursore->voti == maxPtr->voti){
				if (strcmp(cursore->nome, maxPtr->nome) < 0){
					/*SWAP NOMI*/
					char tempNome[10];
					strcpy(tempNome, cursore->nome);
					strcpy(cursore->nome, maxPtr->nome);
					strcpy(maxPtr->nome, tempNome);
				}
			}
			cursore = cursore->nextRappr;
		}
		maxPtr=maxPtr->nextRappr;
	}

}

void stampaVincitori(RapprPtr listPtr){
	int i;
	RapprPtr cursore=listPtr;
	for (i = 0; i < 2; ++i){
		printf("%s con %d voti\n", cursore->nome, cursore->voti);
		cursore=cursore->nextRappr;
	}
}


#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define CIFRE_MATR 5
#define DIM_RIGA 100

#define COND_MATR matr[0] >= 0 && matr[1] >= 0 && matr[2] >= 0 && matr[3] >= 0 && matr[4] >=0
#define COND_VOTO (*voto) >= 0 && (*voto) <= 31

typedef struct stud{

	int matr[CIFRE_MATR];
	float voto_p1;
	float voto_p2;
	float media;
	struct stud* next;

}Studente;

typedef Studente* ListaStudenti;

typedef enum prova{
	P1 = 1,
	P2 = 2
}Prova;

typedef enum bool{
	FALSE = 0,
	TRUE = 1
}Bool;

void mem_error();
void errore_input(void);
void controllo_input(char riga[], int matr[], float *voto);
void insert_in_order(ListaStudenti *lPtr, int matr[],float voto, Prova P);
void calcola_media(ListaStudenti *lPtr);
void stampa_lista_studenti(ListaStudenti lPtr);
Bool is_there(ListaStudenti lPtr, int matr[]);
Bool matr_cmp(int matr1[], int matr2[]);
void cancella_assenti_p2(ListaStudenti *lPtr);

int main(void){

	char riga[DIM_RIGA] ={'\0'};
	ListaStudenti lista_studenti = NULL;
	int matr[CIFRE_MATR] = {0};
	float voto = 0;

	while(fgets(riga,DIM_RIGA,stdin)!= NULL && strcmp("0;0\n", riga) != 0){
		controllo_input(riga, matr, &voto);
		if (voto >= 18)
			insert_in_order(&lista_studenti, matr, voto, P1);
	}
	while(fgets(riga,DIM_RIGA,stdin)!= NULL && strcmp("0;0\n", riga) != 0){
		controllo_input(riga, matr, &voto);
		if (is_there(lista_studenti, matr) && voto >= 18){
			insert_in_order(&lista_studenti, matr, voto, P2);			
		}
	}
	cancella_assenti_p2(&lista_studenti);
	calcola_media(&lista_studenti);
	stampa_lista_studenti(lista_studenti);	
}

void cancella_assenti_p2(ListaStudenti *lPtr){
	while(*lPtr != NULL){
		Studente* precPtr = NULL;
		Studente* corrPtr = (*lPtr);

		if (corrPtr->voto_p2 == 0){

			if (precPtr != NULL){
				Studente* tmpPtr = corrPtr;
				precPtr->next = corrPtr->next;
				free(tmpPtr);
			}
			else{
				Studente* tmpPtr = (*lPtr);
				*lPtr = (*lPtr)->next;
				free(tmpPtr);
			}
		}

		lPtr = &(*lPtr)->next;
	}
}

Bool is_there(ListaStudenti lPtr, int matr[]){
	while(lPtr != NULL){
		if (matr_cmp(matr, lPtr->matr))
			return TRUE;
		
		lPtr = lPtr->next;
	}
	return FALSE;
}

Bool matr_cmp(int matr1[], int matr2[]){
	int i;
	for (i = 0; i < CIFRE_MATR; ++i){
		if (matr1[i] != matr2[i]){
			return FALSE;
		}
	}
	return TRUE;
}

void controllo_input(char riga[], int matr[], float *voto){
	if ((sscanf(riga,"%1d%1d%1d%1d%1d;%f\n", &matr[0], &matr[1], &matr[2], &matr[3], &matr[4], voto)!=6) || !(COND_MATR) || !(COND_VOTO)){
		errore_input();
	}
}

void insert_in_order(ListaStudenti *lPtr, int matr[], float voto, Prova P){

	if (P == P1){
		Studente *newStud = calloc(1, sizeof(Studente));
		if (newStud == NULL){
			mem_error();
			}	
		memcpy(newStud->matr,matr, sizeof(int)*CIFRE_MATR);		
		newStud->voto_p1 = voto;

		if (*lPtr != NULL){

			Studente *precPtr = NULL;
			Studente *corrPtr = (*lPtr);

			/*SALTA TUTTI QUELLI CON VOTO_P1 MAGGIORE*/
			while(corrPtr!= NULL && newStud->voto_p1 < corrPtr->voto_p1){
				precPtr = corrPtr;
				corrPtr = corrPtr->next;
			}
			/*SALTA TUTTI QUELLI CON MATRICOLA MINORE*/
			while(corrPtr!= NULL && newStud->voto_p1 <= corrPtr->voto_p1 && memcmp(corrPtr->matr,matr,sizeof(int)*CIFRE_MATR) < 0 ){
				precPtr = corrPtr;
				corrPtr = corrPtr->next;
			}
			if (precPtr == NULL){
				(*lPtr) = newStud;
				newStud->next = corrPtr;
			}
			else{
			precPtr->next = newStud;
			newStud->next = corrPtr;				
			}

		}
		else{
			*lPtr = newStud;	
		}
	}
	else if (P == P2){
		while(*lPtr != NULL){
			if (memcmp((*lPtr)->matr,matr,sizeof(int)*CIFRE_MATR) == 0){
				(*lPtr)->voto_p2 = voto;
			}
			lPtr =&(*lPtr)->next; 
		}	
	}
}

void calcola_media(ListaStudenti *lPtr){
	while(*lPtr != NULL){
		(*lPtr)->media = ( (*lPtr)->voto_p1 + (*lPtr)->voto_p2 )/2;
		lPtr = &(*lPtr)->next;
	}
}

void stampa_lista_studenti(ListaStudenti lPtr){
	while(lPtr != NULL){
		int i;
		for (i = 0; i < CIFRE_MATR; ++i){
			printf("%d", lPtr->matr[i]);
		}
		printf(" %.2f %.2f %.2f\n", lPtr->voto_p1, lPtr->voto_p2, lPtr->media);
		lPtr = lPtr->next;
	}	
}

void mem_error(){
	puts("memoria esaurita.");
	exit(EXIT_FAILURE);
}

void errore_input(void){
	puts("Errore nell'input.");
	exit(EXIT_FAILURE);
}
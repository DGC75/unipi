#include <stdio.h>
#include <stdlib.h>

#define N 4

typedef struct dipendente{

	int matr;
	char nome[20];
	int mmAssunzione;
	int aaAssunzione;
	int stipendio;

}	Dipendente;

void aumentaStipendio			(Dipendente *dipendentePtr, float percentuale);
void stampaDipendentiAssunti	(Dipendente *dipendentePtr, int size);

int main(void){
	FILE *fPtr = fopen("input.txt", "rb");
	if(fPtr != NULL){
	Dipendente arrDipendenti[N];	
	/*CREA, INIZIALIZZA E METTI NELL'ARRAY 'N' NUOVI DIPENDENTI*/
	int i;
		puts("Matr\tNome\tMM\tAA\tStipendio");
		for (i = 0; i < N; ++i){

			Dipendente *dipendentePtr = calloc(1, sizeof(Dipendente));

			if (dipendentePtr != NULL){
				fread(&arrDipendenti[i], sizeof(Dipendente), 1, fPtr);
				printf("%d\t%s\t%d\t%d\t%d\n",arrDipendenti[i].matr, arrDipendenti[i].nome, arrDipendenti[i].mmAssunzione, arrDipendenti[i].aaAssunzione, arrDipendenti[i].stipendio);
				aumentaStipendio(&arrDipendenti[i], 22);
			}
			else{
			puts("Memoria esaurita");
			exit(EXIT_FAILURE);
			}
		}
		
		fclose(fPtr);
		stampaDipendentiAssunti(arrDipendenti, N);
	}
	else{
		puts("Impossibile aprire file");
		exit(EXIT_FAILURE);
	}
}

void aumentaStipendio(Dipendente *dipendentePtr, float percentuale){
	if ((dipendentePtr->aaAssunzione == 2000 && dipendentePtr->mmAssunzione < 5) || dipendentePtr->aaAssunzione < 2000 ){
		dipendentePtr->stipendio *= ((percentuale/100)+1);
	}
}

void stampaDipendentiAssunti(Dipendente *dipendentePtr, int size){
	int i;
	puts("Matr\tNome\tStipendio");
	for (i = 0; i < N; ++i){
		if (dipendentePtr[i].stipendio > 1200){
			printf("%d\t%s\t%d\n", dipendentePtr[i].matr, dipendentePtr[i].nome, dipendentePtr[i].stipendio);
		}
	}
}
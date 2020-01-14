#include <stdio.h>


#define cornice '*'
#define blocco  'X'
#define righe   10
#define colonne 3


int main (void){
	
	/*STAMPA PRIMA RIGA*/
	for (int primo = 1; primo <= colonne; ++primo){
		printf("%c", cornice);
	}
	printf("\n");

	/*STAMPA DALLA SECONDA ALLA PENULTIMA RIGA*/
    for (int riga = 1; riga <= (righe-2); ++riga){

    	printf("%c", cornice);

    	for (int colonna = 1; colonna <= colonne-2; ++colonna){
    		printf("%c", blocco);
    	}
    	printf("%c\n", cornice);
    }

    /*STAMPA ULTIMA RIGA*/
    for (int ultimo = 1; ultimo <= colonne; ++ultimo){
		printf("%c", cornice);
	}
	printf("\n");
}
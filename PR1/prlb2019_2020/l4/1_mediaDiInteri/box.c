#include <stdio.h>


int main (void){

	int interi=0;
	int count;
	int somma=0;
	/*ACQUISIZIONE INPUT*/
	scanf("%d", &interi);
	/*CONTROLLO DELL'INPUT*/
	while(interi<=0){
		printf("Incorretto. Inserisci un intero positivo.\n");
		scanf("%*[^\n]");
		scanf("%d", &interi);
	}
	/*ACQUISIZIONE E SOMMA INTERI*/
	for (count = 0; count < interi; ++count){
		int input;
		while(scanf("%d", &input)!=1){
			printf("Incorretto. Inserisci un intero.\n");
			scanf("%*[^\n]");
		}
		somma+=input;
	}
	/*CALCOLO E STAMPA OUTPUT*/
	printf("%.2f\n",(float) somma/interi);
}
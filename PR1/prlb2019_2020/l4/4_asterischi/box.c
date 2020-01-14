#include <stdio.h>


int main(void){
	int intero=-1;
	int count;

	/*ACQUISIZIONE INPUT*/
	scanf("%d", &intero);
	/*CONTROLLO INPUT*/
	while(intero<0){
		printf("Incorretto. Inserisci un intero positivo.\n");
		scanf("%*[^\n]");
		scanf("%d", &intero);
	}
	/*STAMPA OUTPUT*/
	for (; intero>0 ; intero-=2){
		for (count=0; count < intero; ++count){
			printf("*");	
		}
		printf("\n");
	}
}
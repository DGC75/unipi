#include <stdio.h>



int main(void){
	int altezza=0, base=0;
	int riga,colonna, spazi;

	/*ACQUISIZIONE E CONTROLLO INPUT*/
	scanf("%d", &altezza);
	while(altezza<=0){
		printf("h incorretto. Introdurre un intero maggiore di 0.\n");
		scanf("%*[^\n]");
		scanf("%d", &altezza);
	}
	scanf("%d", &base);
	while(base<=0){
		printf("l incorretto. Introdurre un intero maggiore di 0.\n");
		scanf("%*[^\n]");
		scanf("%d", &base);
	}

	/*STAMPA OUTPUT*/
	/*STAMPA PRIMA RIGA*/
		for (colonna=0; colonna < base; ++colonna){
			printf("*");
		}
		printf("\n");
	/*STAMPA ALTRE RIGHE*/
		for (riga = altezza-2; riga>0; --riga){
			printf("*");
			for (spazi=base-2; spazi>0; --spazi){
				printf(" ");
			}
			printf("*\n");
		}
	/*STAMPA ULTIMA RIGA*/
	if (altezza>1){
		for (colonna=0; colonna < base; ++colonna){
			printf("*");
		}
		printf("\n");
	}
}
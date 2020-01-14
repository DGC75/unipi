#include <stdio.h>

int factorial(int intero);

int main(void){
	int input=0;
	/*ACQUISIZIONE INPUT*/
	scanf("%d", &input);
	/*CONTROLLO DELL'INPUT E PULIZIA DEL BUFFER*/
	while(input<=0){
		printf("Incorretto. Inserisci un intero positivo.\n");
		scanf("%*[^\n]");
		scanf("%d", &input);
	}
	/*STAMPA OUTPUT*/
	printf("%d\n", factorial(input));
}

/*FUNZIONE FATTORIALE ITERATIVA*/
int factorial(int intero){
	int factorial=intero;
	while(intero>1){
		factorial*=intero-1;
		intero-=1;
	}
	return factorial;
}
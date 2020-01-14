#include <stdio.h>

int main(void){
	int numero;
	int moltiplicatore;
	/*ACQUISIZONE E CONTROLLO INPUT*/
	scanf("%d", &numero);
	while(numero<=0){
		printf("Incorretto. Inserisci un intero positivo.\n");
		scanf("%*[^\n]");
		scanf("%d", &numero);
	}
	/*CALCOLO E STAMPA OUTPUT*/
	for (moltiplicatore = 1; moltiplicatore <= 10; ++moltiplicatore){
		printf("%d\n", numero*moltiplicatore);
	}
}
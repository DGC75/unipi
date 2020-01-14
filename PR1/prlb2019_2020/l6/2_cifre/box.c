#include <stdio.h>

void stampa_cifre(int numero);
void stampa_cifre_inverso(int numero);

int main(void){
	int positivo;
	while(scanf("%d", &positivo)!=1 || positivo<0){
		printf("Errore. Inserisci un intero positivo.\n");
		scanf("%*[^\n]");
		scanf("%*c");
	}
	stampa_cifre(positivo);
	stampa_cifre_inverso(positivo);
}

void stampa_cifre(int numero){
	int cifra=numero;
	printf("%d\n",cifra%10);
	if(cifra/10>0){
		stampa_cifre(cifra/10);
	}
	
}

void stampa_cifre_inverso(int numero){
	int cifra=numero;
	if(cifra>=10){
		stampa_cifre_inverso(cifra/10);
	}
	printf("%d\n",cifra%10);
}



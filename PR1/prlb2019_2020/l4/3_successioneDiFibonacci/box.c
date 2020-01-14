#include <stdio.h>


int main(void){
	/*LETTURA E CONTROLLO INPUT*/
	int numero=0;
	int fibonacci=0;
	int precedente1=0, precedente2=1;
	scanf("%d", &numero);
	while (numero<0){
		printf("Inserire un intero positivo\n");
		scanf("%*[^\n]");
		scanf("%d", &numero);
	}
	/*CALCOLO OUTPUT*/
	while(fibonacci<=numero){
		printf("%d\n",fibonacci);
		precedente1=precedente2;
		precedente2=fibonacci;
		fibonacci=precedente1+precedente2;
	}

}
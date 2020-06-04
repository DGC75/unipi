#include <stdio.h>

int somma_dispari(int val, int count, int acc);

int main(){
	int input;
	
	while(scanf("%d", &input) != 1 || input < 1){
		puts("Input errato. Riprova:");
		scanf("%*[^\n]");
	}

	printf("%d\n", somma_dispari(input, 1, 1));
}

int somma_dispari(int val, int count, int acc){
	
	if(count < val)
		return somma_dispari(val, ++count, acc + (2*count +1) ) ;		
	else
		return acc;
}

#include <stdio.h>






int main (void){
	
	int secondi=0;

	//SCANSIONE INPUT
	scanf("%d", &secondi);
	//CHECK INPUT
	if (secondi<0){
		printf("invalid input\n");
		return 0;
	}
	//CALCOLO & STAMPA ORE, MINUTI E SECONDI
	printf("%d h ", secondi/3600);
		secondi-= 3600*(secondi/3600);

	printf("%d min ", secondi/60);
		secondi-= 60*(secondi/60);	

	printf("%d s\n", secondi);
}
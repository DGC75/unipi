#include <stdio.h>

int Pot2(int positivo);

int main(void){
	int input=0;
	while(scanf("%d", &input)!=1 || input<=0){
		printf("Errore. Inserisci un numero intero positivo\n");
		scanf("%*[^\n]");
		scanf("%*c");
	}
	printf("%d\n",Pot2(input));
}

int Pot2(int positivo){
	static potenze=1;
	if(positivo==1){
		return 2*potenze;
	} else {
		
		potenze*=2;
		return Pot2((positivo-1));
	}
}

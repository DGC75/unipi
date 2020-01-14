#include <stdio.h>

float media(void);

int main(void){
	/*CHIAMATA FUNZIONE E STAMPA OUTPUT*/
	printf("%.2f\n", media());
}



/*FUNZIONE MEDIA*/
float media(void){
	/*VARIABILI*/
	int num_intero;
	int primo_intero;
	int count, addendi=0;
	float somma=0;
	
	for(count=0;count<10;count++){
	/*CONTROLLO INPUT*/	
	while(scanf("%d", &num_intero)!=1){
		printf("Inserisci un intero.\n");
		scanf("%*[^\n]");
	}
	/*CALCOLO OUTPUT*/
	if (count==0){
		primo_intero=num_intero;
	}
	
		if(primo_intero*num_intero>0){
			somma+=num_intero;
			addendi+=1;
		}
	}
	return somma/addendi;
}
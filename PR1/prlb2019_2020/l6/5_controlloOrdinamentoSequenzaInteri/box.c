#include <stdio.h>
#include <stdlib.h>

void controllo_ordinamento();
int get_int();

int main(void){
	controllo_ordinamento();
	puts("Sequenza in ordine strettamente crescente");


}

void controllo_ordinamento(){
	int input;
	static int next;
	input = get_int();
	if (input<0){
		next=next+1;
		return;
	}
	next=input;
	controllo_ordinamento();
	if (next-input<=0){
		puts("Sequenza non in ordine strettamente crescente");
		exit(0);
	}
	next=input;
	return;	
}

int get_int(){
	int temp;
	while(scanf("%d", &temp)!=1 || temp==0){
		puts("Errore. Inserire un numero intero positivo oppure un numero intero negativo per terminare");
		scanf("%*[^\n]");
		scanf("%*c");
	}
	return temp;
}
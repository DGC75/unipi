#include <stdio.h>

#define TIPI_PIASTRELLE_CORTE 2
#define TIPI_PIASTRELLE_LUNGHE 3



long int  conta_possibilita(int n);

int main (void){
	int  int_pos;
	while(scanf("%d", &int_pos)!=1|| int_pos<=0){
		printf("Errore. Inserisci un intero positivo.\n");
		scanf("%*[^\n]");
		scanf("%*c");
	}
	printf("%li\n", conta_possibilita(int_pos));
}


long int  conta_possibilita(int n){
	static long int acc1=2, acc2=7, next=0,i=3;
	if (n==1){
		return 2;
	} else if(n==2){
		return 7;
	} else if(n>2){
		while(i<=n){
			next=3*acc1+2*acc2;
			acc1=acc2;
			acc2=next;
			i++;
		}
		return next;
	}else{
		return 0;
	}
}

 
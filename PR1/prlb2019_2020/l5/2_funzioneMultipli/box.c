#include <stdio.h>

void read_int(void);
void multipli(int sup, int base);

int n=0,m=0;
int main(void){
	
	read_int();
	multipli(n,m);

}


/*CONTROLLO E ASSEGNAMENTO INPUT*/
void read_int(void){
	int input;
	for (int args = 0; args < 2; ++args){
		while(scanf("%d", &input)!=1){
			printf("Inserisci un intero.\n");
			scanf("%*[^\n]");
		}
		if(args==0){
			n=input;
		} else if(args==1){
			m=input;
		}
	}

}

void multipli(int sup, int base){
	int moltiplicatore;
	for (moltiplicatore = 1; moltiplicatore*base <= sup; ++moltiplicatore){
		printf("%d\n", moltiplicatore*base);
	}
}
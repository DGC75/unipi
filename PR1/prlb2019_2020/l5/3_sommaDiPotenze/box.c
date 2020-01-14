#include <stdio.h>
#include <math.h>


int potenza=0;
float base=0;

void read_positive_int(void);
void read_positive_float(void);
float sum_pow(int potenza, float base);

int main(void){
	read_positive_int();
	read_positive_float();
	printf("%.2f\n",sum_pow(potenza, base));

}

void read_positive_int(void){
	while(scanf("%d", &potenza)!=1 || potenza<0){
		printf("Inserisci un intero positivo.\n");
		scanf("%*[^\n]");
	}
}

void read_positive_float(void){
	while(scanf("%f", &base)!=1 || base<0){
		printf("Inserisci un numero reale positivo.\n");
		scanf("%*[^\n]");
	}
}

float sum_pow(int potenza, float base){
	int indice;
	float result=0;
	for ( indice = 0; indice <= potenza; ++indice){
		result+=pow(base, indice);
	}
	return result;
}
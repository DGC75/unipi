#include <stdio.h>
#include <math.h>
float approx_pi(int successione);

int main(void){
	int input;
	while(scanf("%d", &input)!=1 || input<=0){
		printf("Inserisci un intero positivo.\n");
		scanf("%*[^\n]");
		scanf("%*c");
	}
	printf("%.6f\n", approx_pi(input));
}



float approx_pi(int successione){
	int counter=0;
	float result=0;
	while(counter<successione){
		result+= pow(-1,counter)*(float)4/(2*counter+1);
		counter++;

	}
	return result;
}
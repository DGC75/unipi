#include <stdio.h>


void acq_input(int* var);
void swap(int* a, int* b);

int main(){

	int a, b;
	
	acq_input(&a);
	acq_input(&b);
	swap(&a, &b);
	printf("%d\n", a);
	printf("%d\n", b);

	puts("");
}

void acq_input(int* var){
	while(scanf("%d", var) != 1){
		puts("input errato. Riprova");
		scanf("%*[^\n]");
	}	
}

void swap(int* a, int* b){
	*b += *a;
	*a = *b - *a;
	*b -= *a;  
}
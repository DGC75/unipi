#include <stdio.h>

void acq_input(int* var);
void tswap(int* x, int* y, int* z);

int main(){

	int x, y, z;

	acq_input(&x);
	acq_input(&y);
	acq_input(&z);

	tswap(&x, &y, &z);

	printf("%d\n", x);
	printf("%d\n", y);
	printf("%d\n", z);
}

void acq_input(int* var){
	while(scanf("%d", var) != 1){
		puts("Input errato. Riprova:");
		scanf("%*[^\n]");
	}
}

void tswap(int* x, int* y, int* z){
	int tmp = *x;
	int tmp2 = *y;
	*x = *z;
	*y = tmp;
	*z = tmp2;
}
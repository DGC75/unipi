#include <stdio.h>

#define DIM 10

void min_azzera(int array[], size_t dim);

int main(){
	int array[DIM];
	size_t i;
	for (i = 0; i < DIM; ++i){
		scanf("%d",&array[i]);
	}
	min_azzera(array, DIM);	
}

void min_azzera(int array[], size_t dim){
	size_t i;
	int min=array[0];
	for (i = 0; i < dim; ++i){
		if (min>array[i]){
		min=array[i];
		}
		if(i%2==1){
			array[i]=0;
		}
	printf("%d\n", array[i]);
	}
	printf("%d\n", min);
}
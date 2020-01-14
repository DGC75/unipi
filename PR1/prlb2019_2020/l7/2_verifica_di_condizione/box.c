#include <stdio.h>

#define DIM 10


int verifica_condizione(int array[], size_t dim);

int main(){
	int array[DIM];
	size_t i;
	for (i = 0; i < DIM; ++i){
		scanf("%d", &array[i]);
	}
	printf("%d\n", verifica_condizione(array,DIM));
}

int verifica_condizione(int array[], size_t dim){
	size_t i;
	for (i = 1; i < dim-1; ++i){
			if (array[i]== array[i+1]-array[i-1]){
				return i;
			}
		}
	return -1;	
}

#include <stdio.h>

void input_err();
void inverti_array(int* array, size_t dim);
void print_arr(int* array, size_t dim);


int main(){
	int dim;
	while(scanf("%d", &dim) != 1 && dim < 1)
		input_err();

	int i;
	int array[dim];
	for (i = 0; i < dim; ++i){
		scanf("%d", &array[i]);
	}

	inverti_array(array, dim);
	print_arr(array, dim);
	puts("");
}

void input_err(){
	puts("Input errato. Riprova:");
}

void inverti_array(int* array, size_t dim){
	int i;
	for (i = 0; i < dim/2; ++i){
		
		array[dim-i-1] += array[i];
		array[i] = array[dim-i-1] - array[i];
		array[dim-i-1] -= array[i];

	}
}

void print_arr(int* array, size_t dim){
	int i;
	for(i = 0; i < dim; ++i){
		printf("%d\n", array[i]);
	}
}

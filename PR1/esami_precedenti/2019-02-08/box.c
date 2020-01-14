#include <stdio.h>
#include <stdlib.h>

typedef enum bool{
	false = 0,
	true = 1
}Bool;

void acquisisci_input(int *val);

void load_matrix(float **matr, int dim);
void print_matrix(float **matr, int dim);

Bool is_symmetric(float **matr, int dim);
Bool diagonal_null(float **matrix, int dim);

int max_sum_index(float **matrix, int dim, float *tmp);
float sum_column(float **matrix, int dim, int col);

float get_float();


int main(void){

	int N;
	acquisisci_input(&N);

	float* matrix[N];
	int i;
	for (i = 0; i < N; ++i){
		matrix[i] = calloc(N, sizeof(float));
		if (matrix[i] == NULL){
			puts("memoria esaurita");
			exit(EXIT_FAILURE);
		}
	}

	load_matrix(matrix, N);

	if (is_symmetric(matrix, N) && diagonal_null(matrix, N)){
		float sum_max;
		int index = max_sum_index(matrix, N, &sum_max);

		printf("Indice di somma massima: %d\n", index);
		printf("Valore di somma massima: %.2f\n", sum_max);
	}
	else{
		puts("La matrice non contiene distanze valide.");
	}
}

void load_matrix(float **matr, int dim){
	int i,j;
	for (i = 0; i < dim; ++i){
		for (j = 0; j < dim; ++j){
			matr[i][j] = get_float();
		}
	}
}

float sum_column(float **matrix, int dim, int col){
	int i;
	float result = 0;
	for (i = 0; i < dim; ++i){
		result += matrix[i][col];
	}
	return result;
}

void print_matrix(float **matr, int dim){
	int i,j;
	for (i = 0; i < dim; ++i){
		for (j = 0; j < dim; ++j){
			printf("%04.1f\t",matr[i][j] );
		}
		puts("");
	}
}

Bool is_symmetric(float **matr, int dim){
	int i,j;
	for (i = 0; i < dim; ++i){
		for (j = 0; j < dim; ++j){
			if (matr[i][j] != matr[j][i]){
				return false;
			}
		}
	}
	return true;
}

Bool diagonal_null(float **matr, int dim){
	int i;
	for (i = 0; i < dim; ++i){
		if (matr[i][i] != 0){
			return false;
		}
	}
	return true;
}

int max_sum_index(float **matr, int dim, float *tmp){
	int i;
	int index = 0;
	float temp_sum = 0;

	/*CALCOLA PRIMA COLONNA*/
	*tmp = sum_column(matr, dim, 0);
	/*CALCOLA LE ALTRE COLONNE*/

	for (i = 1; i < dim; ++i){
		temp_sum = sum_column(matr, dim, i);
		if (temp_sum > *tmp){
			*tmp = temp_sum;
			index = i;
		}
		temp_sum = 0;
	}
	return index;
}

float get_float(){
	float tmp;
	if (scanf("%f", &tmp) != 1 || tmp < 0){
		puts("Input non corretto.");
		exit(EXIT_FAILURE);
	}
	else{
		return tmp;
	}
}

void acquisisci_input(int *val){
	if (scanf("%d", val)!= 1 || *val <= 0){
		puts("Input non corretto.");
		exit(EXIT_FAILURE);
	}
}
#include <stdio.h>
#include <stdlib.h>

void	loadMatrix(int **matrix, int dim);
void 	diagonal_to_zero(int **matrix, int dim);
void	printMatrix(int **matrix, int dim);
int		readInt();

void free_matr(int **matrix, int dim);

int main(void){

	int dim;
	scanf("%d", &dim);
	int *matrix[dim];
	int i;
	for (i = 0; i < dim; ++i){
		*(matrix +i) = calloc(dim, sizeof(int));
	}

	loadMatrix(matrix, dim);
	diagonal_to_zero(matrix, dim);
	printMatrix(matrix, dim);

	free_matr(matrix, dim);

}

void free_matr(int **matrix, int dim){
	int i;
	for (i = 0; i < dim; ++i){
		free( *(matrix + i));
		*(matrix + i) = NULL;
	}
}

void printMatrix(int **matrix, int dim){

	int i,j;

	for (i = 0; i < dim; ++i){
		for (j = 0; j < dim; ++j){
			printf("%d ", *(*(matrix +i) + j));
		}
		puts("");
	}
}

void loadMatrix(int **matrix, int dim){

	int i,j;

	for (i = 0; i < dim; ++i){
		for (j = 0; j < dim; ++j){
			*(*(matrix + i) + j) = readInt();
		}
	}
}

void diagonal_to_zero(int **matrix, int dim){

	int i,j;
	
	for (i = 0; i < dim; ++i){
		for (j = 0; j < dim; ++j){
			if ( i + j == dim-1 || i==j)
				*( *(matrix + i) + j) = 0;
		}
	}
}

int readInt(){

	int tmp;
	scanf("%d", &tmp);
	return tmp;

}
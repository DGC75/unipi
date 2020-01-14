#include <stdio.h>


#define ROWS 4
#define COLS 3

void loadMatrix(int matrix[][COLS], size_t dim);
void printMatrix(int matrix[][COLS], size_t dim);
void sumMatrix(int matrixA[][COLS], int matrixB[][COLS], int matrixC[][COLS], size_t dim);

int main(){
	int matrixA[ROWS][COLS]; 
	int matrixB[ROWS][COLS]; 
	int matrixC[ROWS][COLS];

	loadMatrix(matrixA, ROWS);
	loadMatrix(matrixB, ROWS);
	sumMatrix(matrixA, matrixB, matrixC, ROWS);

	printMatrix(matrixC, ROWS);
}

void loadMatrix(int matrix[][COLS], size_t dim){
	size_t i,j;
	for ( i = 0; i < dim; ++i){
		for (j = 0; j < COLS; ++j){
			scanf("%d",&matrix[i][j]);	
		}
	}
}

void printMatrix(int matrix[][COLS], size_t dim){
	size_t i,j;
	for (i = 0; i < dim; ++i){
		for (j = 0; j < COLS; ++j){
			printf("%d ",matrix[i][j]);

		}
		puts("");
	}
}

void sumMatrix(int matrixA[][COLS], int matrixB[][COLS], int matrixC[][COLS], size_t dim){
	size_t i,j;
	for (i = 0; i < dim; ++i){
		for (j = 0; j < COLS; ++j){
			matrixC[i][j]=matrixA[i][j]+matrixB[i][j];
		}
	}
}
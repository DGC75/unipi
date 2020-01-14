#include <stdio.h>

#define ROWS_A 4
#define COLS_A 2

#define ROWS_B 2
#define COLS_B 3

#define ROWS_C 4
#define COLS_C 3

void loadMatrixA(int matrix[][COLS_A], size_t dim);
void loadMatrixB(int matrix[][COLS_B], size_t dim);
void multiplyMatrix(int matrixA[][COLS_A],int matrixB[][COLS_B],int matrixC[][COLS_C], size_t dim_A, size_t dim_b, size_t dim_c);
void printMatrixC(int matrix[][COLS_C], size_t dim);

int main(){
	int matrixA[ROWS_A][COLS_A];
	int matrixB[ROWS_B][COLS_B];

	loadMatrixA(matrixA, ROWS_A);
	loadMatrixB(matrixB, ROWS_B);

	int matrixC[ROWS_C][COLS_C]= {0};

	multiplyMatrix(matrixA, matrixB, matrixC, ROWS_A, ROWS_B,ROWS_C);
	printMatrixC(matrixC, ROWS_C);
}

void loadMatrixA(int matrix[][COLS_A], size_t dim){
	size_t i,j;
	for (i = 0; i < dim; ++i){
		for (j = 0; j < COLS_A; ++j){
			scanf("%d", &matrix[i][j]);
		}
	}
}

void loadMatrixB(int matrix[][COLS_B], size_t dim){
	size_t i,j;
	for (i = 0; i < dim; ++i){
		for (j = 0; j < COLS_B; ++j){
			scanf("%d", &matrix[i][j]);
		}
	}
}

void multiplyMatrix(int matrixA[][COLS_A],int matrixB[][COLS_B],int matrixC[][COLS_C], size_t dim_A, size_t dim_B, size_t dim_C){
	size_t i,j;
	size_t s;
	int temp1, temp2;
	/*CAMBIA RIGA DI A*/
	for (i = 0; i < dim_A; ++i){
		/*CAMBIA COLONNA DI B*/
		for (s = 0; s < COLS_B; ++s){
			/*PRODOTTO RIGA*COLONNA*/
			for (j = 0; j < 2; ++j){
				temp1=matrixA[i][j];
				temp2=matrixB[j][s];
				matrixC[i][s]+=temp1*temp2;
			}	
		}
	}
}

void printMatrixC(int matrix[][COLS_C], size_t dim){
	size_t i,j;
	for (i = 0; i < dim; ++i){
		for (j = 0; j < COLS_C; ++j){
			printf("%d ", matrix[i][j]);
		}
		puts("");
	}
}
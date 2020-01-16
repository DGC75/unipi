#include <stdio.h>
#include <stdlib.h>


int read_int();
void mem_error();

int **alloc_2d_matr(int rows, int cols);
void load_2d_matr(int **matr, int rows, int cols);
void multiply_matrices(int **A, int **B, int **C, int n, int m, int s);
void print_2d_matr(int **matr, int rows, int cols);
void free_2d_matr(int **matr, int rows, int cols);


int main(){
	int N, M, S;

	N = read_int();
	M = read_int();
	S = read_int();

	int **matrA = alloc_2d_matr(N, M);	
	int **matrB = alloc_2d_matr(M, S);

	load_2d_matr(matrA, N, M);
	load_2d_matr(matrB, M, S);

	int **matrC = alloc_2d_matr(N, S);
	multiply_matrices(matrA, matrB, matrC, N, M, S);

	print_2d_matr(matrC, N, S);

	free_2d_matr(matrA, N, M);
	free_2d_matr(matrB, M, S);
	free_2d_matr(matrC, N, S);
}


int **alloc_2d_matr(int rows, int cols){
	
	int **tmpMatr = calloc(rows, sizeof(int*));

	if (tmpMatr == NULL)
		mem_error();

	int i;
	for (i = 0; i < rows; ++i){

		tmpMatr[i] = calloc(cols, sizeof(int)); 

		if (tmpMatr[i] == NULL)
			mem_error();
	}

	return tmpMatr;
}
void load_2d_matr(int **matr, int rows, int cols){

	int i,j;

	for (i = 0; i < rows; ++i){
		for (j = 0; j < cols; ++j){
			matr[i][j] = read_int();			
		}
	}
}

void multiply_matrices(int **A, int **B, int **C, int n, int m, int s){

	int i, j, k, tmp = 0;
	for(k = 0; k < s; ++k){
		for(j = 0; j < n; ++j){
			for (i = 0; i < m; ++i){
				tmp+= (A[j][i])*(B[i][k]);
			}
			C[j][k] = tmp;
			tmp = 0;
		}
	}		
}

void print_2d_matr(int **matr, int rows, int cols){
	
	int i,j;
	for (i = 0; i < rows; ++i){
		for (j = 0; j < cols; ++j){
			printf("%d ", matr[i][j]);
		}
		puts("");
	} 
}

void free_2d_matr(int **matr, int rows, int cols){
	
	int i;
	for (i = 0; i < rows; ++i){
		free(matr[i]);
		matr[i] = NULL;
	}
	free(matr);
	matr = NULL;
}

int read_int(){
	
	int tmp;
	scanf("%d", &tmp);
	return tmp;
}

void mem_error(){
	puts("memoria esaurita");
	exit(EXIT_FAILURE);
}

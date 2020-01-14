#include <stdio.h>

#define ROWS 4
#define COLS 3


void loadMatrix(int arr[][COLS], size_t dim);
void printMatrix(int arr[][COLS], size_t dim);
int checkMatrix(int arr[][COLS], size_t dim);

int main(){
	int array[ROWS][COLS];
	loadMatrix(array, ROWS);
	/*printMatrix(array, ROWS);*/
	printf("%d\n", checkMatrix(array, ROWS));

}



void loadMatrix(int arr[][COLS], size_t dim){
	size_t i,j;
	for (i = 0; i < dim; ++i){
		for (j = 0; j < COLS; ++j){
				scanf("%d", &arr[i][j]);
			}	
	}
}

void printMatrix(int arr[][COLS], size_t dim){
	size_t i,j;
	for (i = 0; i < dim; ++i){
		for (j = 0; j < COLS; ++j){
				printf("%d\t", arr[i][j]);
			}
		puts("");	
	}
}


int checkMatrix(int arr[][COLS], size_t dim){
	size_t i,j;
	int temp=-1;
	for (i = 0; i < COLS; ++i){
		for (j = 0; j < dim; ++j){
			if (arr[j][i]%3!=0){
				break;
			}
			temp=i;
		}

		
	}
	return temp;
}
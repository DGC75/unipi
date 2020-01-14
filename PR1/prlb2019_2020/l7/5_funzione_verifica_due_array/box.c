#include <stdio.h>
#include <stdlib.h>

#define DIM 3

void 	loadArr		(int arr[], size_t dim);
void 	check		(int arrA[], int arrB[], size_t dim_a, size_t dim_b);
int  	minArr		(int arr[], size_t dim);

int main(){
	int 		arrA[DIM], arrB[DIM];
	loadArr		(arrA, DIM);
	loadArr		(arrB, DIM);
	check		(arrA, arrB, DIM, DIM);


}

void loadArr(int arr[], size_t dim){
	size_t i;
	for (i = 0; i < dim; ++i){
		scanf("%d",&arr[i]);
	}
}

int  minArr (int arr[], size_t dim){
	size_t i;
	int temp=arr[0];
	for (i = 1; i < dim; ++i){
		if (temp>arr[i]){
			temp=arr[i];
		}		
	}
	return temp;
}

void check(int arrA[], int arrB[], size_t dim_a, size_t dim_b){
	int 	a =	minArr(arrA, dim_a);
	size_t 	i;
	for ( i = 0; i < dim_b; ++i){
		if (a>=arrB[i]){
			puts("FALSE");
			exit(0);
		}
	}
	puts("TRUE");
	exit(0);
}
#include <stdio.h>

void save_int(int *val);
void load_array(int *arr,int dim);
void print_arr(int *arr, int dim);
void merge(int *arr1, int *arr2, int *arrF, int dim1, int dim2, int dimF);
int is_ordered(int *arr, int dim);

int main(){

	int dimA, dimB, dimC;

	save_int(&dimA);
	int arrA[dimA];
	load_array(arrA, dimA);
	puts("Array A:");
	print_arr(arrA, dimA);

	save_int(&dimB);
	int arrB[dimB];
	load_array(arrB, dimB);
	puts("Array B:");
	print_arr(arrB, dimB);	

	dimC = dimA + dimB; 

	int arrC[dimC];
	merge(arrA, arrB, arrC, dimA, dimB, dimC);	
	puts("Array risultato C");
	print_arr(arrC, dimC);

	printf("Ordinato: %d\n", is_ordered(arrC, dimC) ? 1 : 0);

}

int is_ordered(int *arr, int dim){
	int i;
	for(i = 0; i < dim-1; ++i){
		if(arr[i] > arr[i+1])
			return 0;
	}
	return 1;
}

void merge(int *arr1, int *arr2, int *arrF, int dim1, int dim2, int dimF){
	int indA = 0, indB = 0, indC = 0;

	while((indA < dim1) && (indB < dim2)){

		if(arr2[indB] >= arr1[indA])
			arrF[indC++] = arr1[indA++];
		else
			arrF[indC++] = arr2[indB++];
	}

	if(indA == dim1){
		while(indB < dim2){
			arrF[indC++] = arr2[indB++];	
		}
	}
	else{
		while(indA < dim1){
			arrF[indC++] = arr1[indA++];	
		}
	}

}


void save_int(int *val){
	scanf("%d", val);
}

void load_array(int *arr,int dim){

	int i;
	int tmp;

	for (i = 0; i < dim; ++i){
		scanf("%d", &tmp);
		*(arr + i) = tmp;
	}
}

void print_arr(int *arr, int dim){
	int i;
	for (i = 0; i < dim; ++i){
		printf("%d ", *(arr + i));
	}
	puts("");
}


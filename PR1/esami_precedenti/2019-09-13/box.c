#include <stdio.h>
#include <stdlib.h>
#include <math.h>

#define SUM_CONST 100

typedef struct float_node{
	float dato;
	struct float_node* next;
}Float_node;

typedef Float_node* Float_list;

int 	acquisisci_reali(float **arr);
void 	stampa_float_array(float *arr, int dim);
void 	stampa_int_array(int *arr, int dim);
int 	arr_int_max(float *arr, int inizio, int fine);
int 	num_divisori_arr(int input, float *input_arr, int dim, int **output_arr);
void 	insert(Float_list* lPtr, float val);
void 	mem_error();
float* 	crea_array(Float_list lPtr, int dim);

int main(void){

	float *array_r = NULL;

	int dim = acquisisci_reali(&array_r);
	printf("Array:\n");
	stampa_float_array(array_r, dim);

	int int_max = arr_int_max(array_r, 0, dim-1);

	if (int_max != -1){
		puts("Intero massimo:");
		printf("%d\n", int_max);		
	}
	else{
		puts("Nessun intero positivo.");
		exit(EXIT_SUCCESS);
	}

	int *div_max_arr = NULL;

	dim = num_divisori_arr(int_max, array_r, dim, &div_max_arr);
	puts("Divisori di max:");
	stampa_int_array(div_max_arr, dim);
}

float* crea_array(Float_list lPtr, int dim){

	if (dim == 0){	
		puts("hai acquisito zero interi");
		exit(EXIT_FAILURE);
	}
	float* result = calloc(dim, sizeof(float));

	int i;
	for (i = 0; i < dim && lPtr != NULL; ++i){
		result[i] = (lPtr->dato);
		lPtr = lPtr->next;
	}

	return result;
}

int acquisisci_reali(float **input_arr){

	Float_list r_list = NULL;
	float temp, somma = 0;
	int result = 0;

	while(somma <= SUM_CONST){

		scanf("%f", &temp);
		scanf("%*[^\n]");
		scanf("%*c");

		insert(&r_list, temp);
		somma += temp;
		++result;
	}
	(*input_arr) = crea_array(r_list, result);
	return result;
}

void insert(Float_list* lPtr, float val){

	Float_node *newNode = calloc(1, sizeof(Float_node));
	if (newNode == NULL){
			mem_error();
	}
	newNode->dato = val;

	if (*lPtr == NULL){
		*lPtr = newNode;
	}
	else{
		Float_node *precPtr = (*lPtr);
		Float_node *corrPtr = (*lPtr)->next;
		while(corrPtr != NULL){
			precPtr = corrPtr;
			corrPtr = corrPtr->next;
		}
		precPtr->next = newNode;
	}
}

int arr_int_max(float *arr, int inizio, int fine){
	
	if (fine-inizio >=1){

		int centro1 = (inizio +fine)/2;
		int centro2 = centro1+1;

		int a = arr_int_max(arr, inizio, centro1);
		int b = arr_int_max(arr, centro2, fine);

		if(a >= b)
			return a;
		else
			return b;
	}
	else{
		if (arr[inizio] >= 0 && ( (ceil(arr[inizio]) - arr[inizio]) == 0) ){
			return arr[inizio];
		}
		else{
			return -1;
		}
	}
}

void stampa_float_array(float *arr, int dim){

	int i;
	for(i = 0; i < dim-1; i++){
		printf("%.2f ", arr[i]);
	}
	printf("%.2f\n", arr[dim-1]);
}

void stampa_int_array(int *arr, int dim){
	int i;
	for(i = 0; i < dim-1; i++){
		printf("%d ", arr[i]);
	}
	printf("%d\n", arr[dim-1]);
}

int num_divisori_arr(int input, float *input_arr, int dim, int **output_arr){

	int i,j, result = 0;

	for (i = 0; i < dim; ++i){
		if ( (input_arr[i]- ceil(input_arr[i]) == 0) && (input_arr[i] >=0) && (!(input%((int)input_arr[i]) != 0)) ){
			++result;
		}
	}
	int *newArr = calloc(result, sizeof(int));
	for (i = 0, j = 0; (i < dim) && (j < result); ++i){
			if ( (input_arr[i]- ceil(input_arr[i]) == 0) && (input_arr[i] >=0) && (!(input%((int)input_arr[i]) != 0)) ){
				newArr[j] = input_arr[i];
				++j;
			}
	}
	*output_arr = newArr;
	return result;
}

void mem_error(){
	puts("memoria esaurita");
	exit(EXIT_FAILURE);
}
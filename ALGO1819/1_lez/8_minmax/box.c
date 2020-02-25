#include <stdio.h>

#define DIM 10

void minmax(int* arr, size_t dim, int *min, int* max);

int main(){
	
	int arr[DIM] = {0};
	int i;
	for(i = 0; i < DIM; ++i){

		scanf("%d", &arr[i]);
		scanf("%*[^\n]");

	}
	
	int pos_min, pos_max;
	minmax(arr, DIM, &pos_min, &pos_max);
	
	printf("%d\n", pos_min);
	printf("%d\n", arr[pos_min]);

	printf("%d\n", pos_max);
	printf("%d\n", arr[pos_max]);	

}

void minmax(int* arr, size_t dim, int *min, int* max){
	
	int i = 0;
	*min = i;
	*max = i; 

	for(i = 0; i < dim; ++i){
		if(arr[i] < arr[*min])
			*min = i;

		if(arr[i] > arr[*max])
			*max = i;	
	}
}

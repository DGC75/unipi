#include <stdio.h>

#define BASE 10


void reset(int array[], int len);
void add(int array[], int len, int val);
void print_arr(int arr[], size_t dim);

int main(){

	int input = 0;
	int arr[BASE];

	reset(arr, BASE);

	while(scanf("%d", &input) == 1 && input > -1)
		add(arr, BASE, input);

	print_arr(arr, BASE);
}

void print_arr(int arr[], size_t dim){
	int i;
	for(i = 0; i < dim; ++i){
		printf("%d\n", arr[i]);
	}
}

void reset(int array[], int len){
	int i;
	for(i = 0; i < len; ++i)
		array[i] = 0;	
}

void add(int array[], int len, int val){
	if(val >= 0 && val <= len-1){
		array[val]++;
	}
}
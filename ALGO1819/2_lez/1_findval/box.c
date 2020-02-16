#include <stdio.h>


#define DIM 10


int* FindVal(int a[], int len, int val);


int main(){
	
	int arr[DIM] = {0};
	int i, val;
	for(i = 0; i < DIM; ++i){
		
		scanf("%d", &arr[i]);
		scanf("%*[^\n]");		
	}


	scanf("%d", &val);

	if( FindVal(arr, DIM, val) != NULL)
		puts("trovato");
	else
		puts("non trovato");
}

int* FindVal(int a[], int len, int val){

	int i;
	for(i = 0; i < len; ++i){
		if(a[i] == val)
			return &a[i];
	}
	return NULL;
}
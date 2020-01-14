#include <stdio.h>

#define NMAX 100

int get_int();
int get_int_pos();

int main(){
	int n=get_int_pos();
	int array[n];
	size_t i;
	for (i = 0; i < n; ++i){
		array[i]=get_int();
	}
	for (i = 0; i < n; ++i){
		if(array[i]>=0 && array[i]%2==0){
			printf("%d\n", array[i]);
		}else if(array[i]<0 && i<9 && array[i+1]>=0){
			printf("%d\n", array[i]);	
		}
	}
}

int get_int_pos(){
	int temp;
	do{
		while(scanf("%d", &temp)!=1){
			puts("Inserisci un intero.");
			scanf("%*[^\n]");
			scanf("%*c");
		}
		if(temp<=0 || temp>NMAX){
			puts("Inserisci un intero positivo compreso fra 1 e 100.");	
		}
	
	}while(temp<=0 || temp>NMAX);

	return temp;
}
int get_int(){
	int temp;
		while(scanf("%d", &temp)!=1){
			puts("Inserisci un intero.");
			scanf("%*[^\n]");
			scanf("%*c");
		}
	return temp;
}
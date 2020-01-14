#include <stdio.h>


int main(void){
	int i,j;
	int array[10];
	for (i = 0; i < 10; ++i){
		scanf("%d",&array[i]);
	}
	for (j = 9; !(j<0); --j){
		if (array[j]%2==0){
			array[j]/=2;
		}
		printf("%d\n",array[j]);	
	}
}

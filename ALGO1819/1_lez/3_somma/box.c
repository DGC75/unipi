#include <stdio.h>


int main(void){

	int input;
	int output = 0;

	while(scanf("%d", &input) && input != 0)
		output += input;
	
	printf("%d\n", output);
}
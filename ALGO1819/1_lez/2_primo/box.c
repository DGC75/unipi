#include <stdio.h>

void input_error();

int main(){
	int input; 
	while(scanf("%d", &input) != 1 || input < 1)
		input_error();

	if(input == 1)
		puts("0");
	else if(input == 2)
		puts("1");
	else{
		int divisor = 2;
		while(divisor <= input){
			if(input % divisor == 0 && input != divisor){
				puts("0");
				return 0;
			}	
			else{
				divisor++;
			}
		}
		puts("1");
	}
}


void input_error(){
	puts("Input non corretto. Riprova:");
}
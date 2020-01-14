#include <stdio.h>
#include <stdbool.h>

#define STRINGHE 3

void palindromaConSeparatore(void);

_Bool isPalindrome=true;

int main(void){
	int counter;
	
	for (counter= 0; counter < STRINGHE; ++counter){
		palindromaConSeparatore();
		if(isPalindrome){
		printf("palindrome\n");
		} else {
			printf("non palindrome\n");
		}
		isPalindrome=true;
	}

}

void palindromaConSeparatore(void){
	char c;
	c=getchar();
	if(c=='*'){
		return;
	}
	palindromaConSeparatore();
	if (c==getchar()){
		return;
	} else if (isPalindrome!=false){
		isPalindrome=false;
	}
}


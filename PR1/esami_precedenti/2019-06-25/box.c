#include <stdio.h>
#include <ctype.h>
#include <stdlib.h>

#define IS_OPERATOR (str[i] == '+') || (str[i] == '-') || (str[i] == '*') || (str[i] == '/') || (str[i] == '%') || (str[i] == '=')
#define IS_PARENTHESIS (str[i] == '(') || (str[i] == ')')

typedef enum bool{
	false = 0,
	true = 1
}Bool;

void acquisisci_input(int *val);
Bool isCorrect(char *str, int dim);
Bool alphabet_correct(char *str, int dim);
Bool syntax_correct(char *str, int dim);

int main(void){
	int str_len; 
	acquisisci_input(&str_len);

	char espressione[str_len+1];
	fgets(espressione,str_len+1,stdin);
	espressione[str_len] = '\0';

	if (isCorrect(espressione, str_len))
		puts("espressione corretta");
	else
		puts("espressione non corretta");
}

void acquisisci_input(int *val){
	if (scanf("%d", val)!= 1 || *val <= 0){
		puts("input non corretto");
		exit(EXIT_FAILURE);
	}
	scanf("%*[^\n]");
	scanf("%*c");
}

Bool isCorrect(char *str, int dim){
	if ( alphabet_correct(str, dim) && syntax_correct(str, dim))
		return true;
	else
		return false;
}

Bool alphabet_correct(char *str, int dim){
	int i;
	for (i = 0; i < dim; ++i){
		if ( (!isalnum(str[i])) && !(IS_PARENTHESIS) && !(IS_OPERATOR))
			return false;
	}
	return true;
}

Bool syntax_correct(char *str, int dim){
	int stack = 0;
	int i;
	for (i = 0; i < dim; ++i){
		if (str[i] == '(' ){
			++stack;	
		}
		else if(str[i] == ')' ){
			--stack;
		}
		if (stack < 0){
			return false;
		}
	}
	if (stack == 0)
		return true;
	else
		return false;
	
}

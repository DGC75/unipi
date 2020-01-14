#include <stdio.h>
#include <stdlib.h>

typedef enum bool{
	false = 0,
	true = 1
}Bool;

typedef struct nodo{
	char dato;
	struct nodo* next;
}Nodo;

typedef Nodo* Lista;


void acquisisci_input(int *val);
void mem_error();

void push(Lista *stack, char val);
char pop(Lista *stack);
Bool check_palindrome(Lista *stack,int inizio, int fine);


int main(void){

	int dim;
	acquisisci_input(&dim);

	Lista stack = NULL;

	/*ACQUISIZIONE STRINGA*/
	char c = getchar();
	int i;

	for(i = 0; i < dim && c != '\n'; i++ ){
		push(&stack, c);
		c = getchar();
	}
	if(check_palindrome(&stack,0, dim-1))
		puts("Stringa palindroma");
	else
		puts("Stringa non palindroma");
}

Bool check_palindrome(Lista *stack,int inizio, int fine){

	if( (fine - inizio) == 0){
		pop(stack);
		return true;
	}

	if ( (fine - inizio) == 1){
		if( pop(stack) == pop(stack))
			return true;
		else
			return false;
	}
	else{
		char c = pop(stack);
		if (check_palindrome(stack, ++inizio, --fine)){		
			
			char d = pop(stack);
			if (c == d){
				return true;
			}
			else{
				return false;	
			}
		}
	}
	return false; 
}

void push(Lista *stack, char val){

	Nodo* newNode = calloc(1, sizeof(Nodo));
	if (newNode == NULL){
		mem_error();
	}
	newNode->dato = val;

	if (*stack == NULL){
		*stack = newNode;
	}
	else{
		newNode->next = *stack;
		*stack = newNode;
		
	}
}

char pop(Lista *stack){
	if (*stack == NULL){
		puts("stai facendo il pop ad uno stack vuoto");
		exit(EXIT_FAILURE);
	}
	else{
		char result = (*stack)->dato;
		Nodo* tmpPtr = (*stack);
		*stack = (*stack)->next;
		free(tmpPtr);

		return result;
	}
}


void acquisisci_input(int *val){
	if (scanf("%d", val) != 1 || *val <= 0){
		puts("Input non corretto");
		exit(EXIT_FAILURE);
	}
	scanf("%*[^\n]");
	scanf("%*c");
}

void mem_error(){
	puts("memoria esaurita");
	exit(EXIT_FAILURE);
}
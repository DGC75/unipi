#include <stdio.h>
#include <stdlib.h>


typedef enum{false,true} boolean;

typedef struct intero{
	int dato;
	struct intero* next;
}Intero;

typedef Intero* ListaInteri;


void insert_t(ListaInteri *lPtr, int input);
boolean is_ordered(ListaInteri lPtr);
void mem_error();

int main (void){
	ListaInteri lst = NULL;
	int input;

	while(scanf("%d", &input) == 1 && input >= 0)
		insert_t(&lst, input);

	if(is_ordered(lst))
		puts("True");
	else
		puts("False");
}

void insert_t(ListaInteri *lPtr, int input){

	Intero* newIntero = calloc(1, sizeof(Intero));
	if(newIntero == NULL)
		mem_error();

	newIntero->dato = input;

	if (*lPtr == NULL){
		*lPtr = newIntero;
	}
	else{

		while((*lPtr)->next != NULL)
			lPtr = &(*lPtr)->next;

		(*lPtr)->next = newIntero;
	}
}

boolean is_ordered(ListaInteri lPtr){
	if (lPtr != NULL){

		ListaInteri head = lPtr;
		ListaInteri tail = NULL;

		if ((head)->next != NULL){
			tail = (head)->next;

			if ((head)->dato < (tail)->dato ){
				return is_ordered(tail);
			}
			else{
				return false;
			}
		}
		return true;
	}
	return true;
}

void mem_error(){
	puts("Memoria esaurita");
	exit(EXIT_FAILURE);
}
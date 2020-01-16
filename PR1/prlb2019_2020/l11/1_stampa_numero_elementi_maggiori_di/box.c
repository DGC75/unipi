#include <stdio.h>
#include <stdlib.h>

typedef struct intero{
	int dato;
	struct intero *next;
}Intero;

typedef Intero* ListaInteri;

void add_end(ListaInteri *lPtr);
void insert_t(ListaInteri *lPtr, int val);
int  CalcoloSomma(ListaInteri lPtr, int acc);
int  CalcoloNElementi(ListaInteri lPtr, float num, int acc);

void mem_error();
void free_lst(ListaInteri *lPtr);

int main(){
	
	ListaInteri lst = NULL;
	int somma;
	add_end(&lst);

	somma = CalcoloSomma(lst, 0);
	printf("%d\n", somma);
	printf("%d\n", CalcoloNElementi(lst, somma/4, 0));

	free_lst(&lst);
}

void free_lst(ListaInteri *lPtr){
	if (*lPtr != NULL){
		if ((*lPtr)->next != NULL){
			free_lst(&(*lPtr)->next);
		}
		free(*lPtr);
		(*lPtr)= NULL;
	}
	lPtr = NULL;
}

void add_end(ListaInteri *lPtr){

	int input;
	while(scanf("%d", &input) == 1 && input >=0){
		insert_t(lPtr, input);
	}
}

void insert_t(ListaInteri *lPtr, int val){

	Intero *newIntero = calloc(1, sizeof(Intero));

	if(newIntero == NULL)
		mem_error();

	newIntero->dato = val;

	if(*lPtr == NULL){
		*lPtr = newIntero;
	}
	else{
		while((*lPtr)->next != NULL){
			lPtr = &(*lPtr)->next;
		}
		(*lPtr)->next = newIntero;
	}
}

int CalcoloSomma(ListaInteri lPtr, int acc){
	if(lPtr == NULL)
		return acc;
	else
		return CalcoloSomma(lPtr->next, acc + lPtr->dato);
}	

int CalcoloNElementi(ListaInteri lPtr, float num, int acc){
	if(lPtr == NULL)
		return acc;
	else{
		if ((float)lPtr->dato > num)
			return CalcoloNElementi(lPtr->next, num, ++acc);
		else
			return CalcoloNElementi(lPtr->next, num, acc);
	}
}

void mem_error(){
	puts("memoria esaurita");
	exit(EXIT_FAILURE);
}
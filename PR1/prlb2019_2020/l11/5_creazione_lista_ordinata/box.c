#include <stdio.h>
#include <stdlib.h>


typedef struct intero{
	int dato;
	struct intero *next;
}Intero;

typedef Intero* ListaInteri;

void add_ord(ListaInteri *lPtr);
void ins_ord(ListaInteri *lPtr, int val);
void print_lst(ListaInteri lPtr);
Intero* allocNewIntero(int val);

void free_lst(ListaInteri *lPtr);

void mem_error();

int main(void){

	ListaInteri lst = NULL;
	add_ord(&lst);
	print_lst(lst);
	free_lst(&lst);
}

void add_ord(ListaInteri *lPtr){
	int tmp;
	while(scanf("%d", &tmp) == 1 && tmp > -1 )
		ins_ord(lPtr, tmp);
}

void ins_ord(ListaInteri *lPtr, int val){

	Intero* newIntero = allocNewIntero(val);

	if(*lPtr == NULL)
		*lPtr = newIntero;
	else{
		if(val < (*lPtr)->dato){
			newIntero->next = *lPtr;
			*lPtr = newIntero;
		}
		else{
			Intero* precPtr = *lPtr;
			Intero* corrPtr = (*lPtr)->next;

			while(corrPtr != NULL && val > corrPtr->dato){
				precPtr = corrPtr;
				corrPtr = corrPtr->next;
			}

			precPtr->next = newIntero;
			newIntero->next = corrPtr;
		}
	}
}

Intero* allocNewIntero(int val){
	Intero *newIntero = calloc(1, sizeof(Intero));
	if(newIntero == NULL)
		mem_error();

	newIntero->dato = val;
	return newIntero;
}

void free_lst(ListaInteri *lPtr){
	if(*lPtr != NULL){
		free_lst(&(*lPtr)->next);
		free(*lPtr);
		*lPtr = NULL;
	}
}
void print_lst(ListaInteri lPtr){
	if(lPtr == NULL)
		puts("NULL");
	else{
		printf("%d -> ", lPtr->dato);
		print_lst(lPtr->next);
	}
}

void mem_error(){
	puts("Memoria esaurita.");
	exit(EXIT_FAILURE);
}
#include <stdio.h>
#include <stdlib.h>

typedef struct intero{
	int dato;
	struct intero* next;
}Intero;

typedef Intero* ListaInteri;

void mem_error();
Intero* allocNewIntero(ListaInteri *lPtr, int val);
void init_lst(ListaInteri *lPtr);
void print_lst(ListaInteri lPtr);
void cancellaDuplicates(ListaInteri *lPtr);
void filter(ListaInteri *lPtr1, ListaInteri *lPtr2);
void free_lst(ListaInteri *lPtr);

int main(){

	ListaInteri lst1 = NULL;
	ListaInteri lst2 = NULL;

	init_lst(&lst1);
	init_lst(&lst2);

	puts("Primo elenco:");
	print_lst(lst1);

	cancellaDuplicates(&lst1);
	puts("Primo elenco senza duplicati:");
	print_lst(lst1);

	puts("Secondo elenco:");
	print_lst(lst2);

	cancellaDuplicates(&lst2);
	puts("Secondo elenco senza duplicati:");
	print_lst(lst2);

	filter(&lst1, &lst2);
	puts("Primo elenco filtrato:");
	print_lst(lst1);

	free_lst(&lst1);
	free_lst(&lst2);

	return 0;
}

void free_lst(ListaInteri *lPtr){
	if(*lPtr != NULL){
		free_lst(&(*lPtr)->next);
		free(*lPtr);
		*lPtr = NULL;
	}
}

void mem_error(){
	puts("Memoria esaurita.");
	exit(EXIT_FAILURE);
}

Intero* allocNewIntero(ListaInteri *lPtr, int val){
	
	Intero* newIntero = calloc(1, sizeof(Intero));
	
	if(newIntero == NULL)
		mem_error();

	newIntero->dato = val;
	return newIntero;
}
void init_lst(ListaInteri *lPtr){
	
	int last, new;
	scanf("%d", &last);
	Intero *newIntero = allocNewIntero(lPtr, last);

	*lPtr = newIntero;

	scanf("%d", &new);
	while(new >= last){

		newIntero = allocNewIntero(lPtr, new);
		
		while( (*lPtr)->next != NULL){
			lPtr = &(*lPtr)->next;
		}
		(*lPtr)->next = newIntero;

		last = new;
		scanf("%d", &new);
	}
}

void print_lst(ListaInteri lPtr){
	printf("(");
	while(lPtr != NULL){
		printf("%d ", lPtr->dato);
		lPtr = lPtr->next;
	}
	printf(")\n");
}

void cancellaDuplicates(ListaInteri *lPtr){
	if(*lPtr != NULL && (*lPtr)->next != NULL){
		if((*lPtr)->dato == ((*lPtr)->next)->dato){

			Intero *tmpPtr = *lPtr;
			*lPtr = (*lPtr)->next;
			free(tmpPtr);
			tmpPtr = NULL;
			cancellaDuplicates(lPtr);	
		}
	cancellaDuplicates(&(*lPtr)->next);	
	}
}
void filter(ListaInteri *lPtr1, ListaInteri *lPtr2){
	while(*lPtr2 != NULL){

		if (*lPtr1 != NULL && (*lPtr1)->dato == (*lPtr2)->dato){
			
			Intero* tmpPtr = *lPtr1;
			*lPtr1 = (*lPtr1)->next;
			free(tmpPtr);
			tmpPtr = NULL;
		}
		lPtr2 = &(*lPtr2)->next;
	}
}
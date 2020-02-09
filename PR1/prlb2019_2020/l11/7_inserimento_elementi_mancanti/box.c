#include <stdio.h>
#include <stdlib.h>

#define MIN_VAL 0

typedef struct intero{
	int dato;
	struct intero* next;
}Intero;

typedef Intero* ListaInteri;

void    add_ord(ListaInteri *lPtr, int val);
void	ins_ord(ListaInteri *lPtr);
void	ins_miss_el(ListaInteri *lPtr);	
void 	print_lst(ListaInteri lPtr);	
void 	free_lst(ListaInteri *lPtr);
void	mem_error();
Intero* allocNewIntero(int val);

int main(){

	ListaInteri lst = NULL;
	
	ins_ord(&lst);
	ins_miss_el(&lst);
	
	print_lst(lst);
	
	free_lst(&lst);
	return 0;
}

void add_ord(ListaInteri *lPtr, int val){
	Intero* newIntero = allocNewIntero(val);

	if(*lPtr == NULL)
		*lPtr = newIntero;
	else{
		if(val >= (*lPtr)->dato){
			
			newIntero->next = *lPtr;
			*lPtr = newIntero;
		
		}
		else{
			Intero* precPtr = *lPtr;
			Intero* corrPtr = (*lPtr)->next;

			while(corrPtr != NULL && val < corrPtr->dato){
				precPtr = corrPtr;
				corrPtr = corrPtr->next;
			}

			precPtr->next = newIntero;
			newIntero->next = corrPtr;
		}
	}
}

void ins_ord(ListaInteri *lPtr){

	int tmp;
	while(scanf("%d", &tmp) == 1 && tmp >= MIN_VAL)
		add_ord(lPtr, tmp);

}
void ins_miss_el(ListaInteri *lPtr){
	if(*lPtr != NULL){
		Intero* precPtr = NULL;
		Intero* corrPtr = *lPtr;

			precPtr = corrPtr;
			corrPtr = corrPtr->next;

		while(corrPtr != NULL){

			if(precPtr->dato - corrPtr->dato > 1){
				int range = precPtr->dato - corrPtr->dato - 1;
				int upper = precPtr->dato;
				int i;
				for(i = 1; i <= range; i++){
					Intero *newIntero = allocNewIntero(upper - i);
					precPtr->next = newIntero;
					newIntero->next = corrPtr;
					precPtr= precPtr->next;				
				}
			}

			precPtr = corrPtr;
			corrPtr = corrPtr->next;
		
		}

	}
}	

Intero* allocNewIntero(int val){

	Intero* newIntero = calloc(1, sizeof(Intero));
	if(newIntero == NULL)
		mem_error();

	newIntero->dato = val;

	return newIntero;
}

void print_lst(ListaInteri lPtr){
	if(lPtr == NULL)
		puts("NULL");
	else{
		printf("%d --> ", lPtr->dato);
		print_lst(lPtr->next);
	}

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
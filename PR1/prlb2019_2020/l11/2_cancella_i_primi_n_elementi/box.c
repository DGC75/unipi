#include <stdio.h>
#include <stdlib.h>

typedef struct intero{
	int dato;
	struct intero *next;
}Intero;

typedef Intero* ListaInteri;

void add_end(ListaInteri *lPtr);
void delete_h(ListaInteri *lPtr);
void el_lst(ListaInteri *lPtr, int n);
void print_lst(ListaInteri lPtr);
void insert_t(ListaInteri *lPtr, int val);

int save_int();
void mem_error();
void free_lst(ListaInteri *lPtr);

int main(void){

	ListaInteri lst = NULL;
	add_end(&lst);	
	int n = save_int();
	el_lst(&lst, n);
	print_lst(lst);
	free_lst(&lst);

}

void add_end(ListaInteri *lPtr){
	int input;
	while(scanf("%d", &input)==1 && input >= 0)
		insert_t(lPtr, input);
}

void insert_t(ListaInteri *lPtr, int val){
	
	Intero *newIntero = calloc(1, sizeof(Intero));
	if(newIntero == NULL)
		mem_error();

	newIntero->dato = val;

	if (*lPtr == NULL)
		(*lPtr) = newIntero;
	else{
		while((*lPtr)->next != NULL)
			lPtr = &(*lPtr)->next;

		(*lPtr)->next = newIntero;
	}
}

void delete_h(ListaInteri *lPtr){

	if(*lPtr != NULL){
		Intero *tmp = (*lPtr);
		(*lPtr) = (*lPtr)->next;
		free(tmp);
		tmp = NULL;
	}
}
void el_lst(ListaInteri *lPtr, int n){
	if(n > 0 && (*lPtr) != NULL){
		delete_h(&(*lPtr));
		el_lst(lPtr, n-1);
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

void free_lst(ListaInteri *lPtr){
	if(*lPtr != NULL){
		free_lst(&(*lPtr)->next);
		free(*lPtr);
	}
}

int save_int(){
	int tmp;
	scanf("%d", &tmp);
	return tmp;
}

void mem_error(){
	puts("memoria esaurita");
	exit(EXIT_FAILURE);
}
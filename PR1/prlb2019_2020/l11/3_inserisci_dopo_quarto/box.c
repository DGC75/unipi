#include <stdio.h>
#include <stdlib.h>

typedef struct intero{
	int dato;
	struct intero* next;
} Intero;

typedef Intero* ListaInteri;

void add_end(ListaInteri *lPtr);
void insert_t(ListaInteri *lPtr, int val);
void add_after_fourth(ListaInteri *lPtr, int val);
void print_lst(ListaInteri lst);

void mem_error();

int main(void){

	ListaInteri lst = NULL;
	add_end(&lst);

	int n;
	scanf("%d", &n);

	add_after_fourth(&lst, n);

	print_lst(lst);
}

void add_end(ListaInteri *lPtr){

	int val;
	while(scanf("%d", &val) == 1 && val >= 0)
		insert_t(lPtr, val);

}

void insert_t(ListaInteri *lPtr, int val){

	Intero* newIntero = calloc(1, sizeof(Intero));

	if(newIntero == NULL)
		mem_error();

	newIntero->dato = val;

	if(*lPtr == NULL)
		*lPtr = newIntero;
	else{
		while((*lPtr)->next != NULL)
			lPtr = &(*lPtr)->next;

		(*lPtr)->next = newIntero; 
	}

}

void add_after_fourth(ListaInteri *lPtr, int val){
	
	static int acc = 1;

	if(acc >= 4 || (*lPtr) == NULL){
		if(*lPtr == NULL)
			insert_t(lPtr, val);
		else{

			Intero *newIntero = calloc(1, sizeof(Intero));

			if(newIntero == NULL)
				mem_error();

			newIntero->dato = val;

			Intero *tmp = (*lPtr)->next;
			(*lPtr)->next = newIntero;
			newIntero->next = tmp;
		}	
	}	
	else{
		acc++;
		add_after_fourth(&(*lPtr)->next, val);
	}
}


void print_lst(ListaInteri lst){

	if(lst == NULL)
		puts("NULL");
	else{
		printf("%d -> ", lst->dato);
		print_lst(lst->next);
	}

}

void mem_error(){
	puts("memoria esaurita");
	exit(EXIT_FAILURE);
}
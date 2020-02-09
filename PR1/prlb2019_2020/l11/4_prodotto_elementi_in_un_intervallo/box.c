#include <stdio.h>
#include <stdlib.h>

typedef struct intero{
	int dato;
	struct intero* next;
}Intero;

typedef Intero* ListaInteri;

void insert_o(ListaInteri *lPtr, int val);
int  prod_interval(ListaInteri lPtr, int N, int M);
void add_ord_unique(ListaInteri* lPtr);
Intero* createNewNode(int val);

int  save_int();
void free_lst(ListaInteri *lPtr);	
void mem_error();

void print_lst(ListaInteri lPtr);

int main(void){

	ListaInteri lst = NULL;

	int N = save_int();
	int M = save_int();
	


	add_ord_unique(&lst);
	printf("%d\n", prod_interval(lst, N, M));

	free_lst(&lst);	
}


void print_lst(ListaInteri lPtr){
	while(lPtr != NULL){
		printf("%d -> ", lPtr->dato);
		lPtr = lPtr->next;
	}
	puts("NULL");
}

int prod_interval(ListaInteri lPtr, int N, int M){
	
	int result = 1;
	if(lPtr == NULL)
		return -1;
	else
		if(lPtr->dato > N){
			while(lPtr->next != NULL && lPtr->dato < M){
				result *= lPtr->dato;
				lPtr=lPtr->next;
			}
			return result;
		}
		else{
			int temp = prod_interval(lPtr->next, N, M);
			return (temp > 0 ? temp : 1);
		}
}

void insert_o(ListaInteri *lPtr, int val){

	Intero *newIntero = createNewNode(val);

	if(*lPtr == NULL){
		*lPtr = newIntero;
	}
	else{
		if(val < (*lPtr)->dato){
			newIntero->next = *lPtr;
			*lPtr = newIntero;
		}
		else{

			Intero *precPtr = *lPtr;
			Intero *corrPtr = (*lPtr)->next;	

			while(val > precPtr->dato && corrPtr != NULL){
				precPtr = corrPtr;
				corrPtr = corrPtr->next;
			}

			if (val != precPtr->dato){
				if(corrPtr == NULL)
					precPtr->next = newIntero;

				else if(val != corrPtr->dato){

					precPtr->next = newIntero;
					newIntero->next = corrPtr;
				}
			}


		}
	}
	
}	

Intero* createNewNode(int val){

	Intero* newIntero = calloc(1, sizeof(Intero));
	
	if(newIntero == NULL)
		mem_error();

	newIntero->dato = val;

	return newIntero;
}

void add_ord_unique(ListaInteri *lPtr){

	int val;
	while(scanf("%d", &val) == 1 && val >= 0)
		insert_o(lPtr, val);
}

void free_lst(ListaInteri *lPtr){
	
	if(*lPtr != NULL){	

		while((*lPtr)->next != NULL)
			free_lst(&(*lPtr)->next);

		free(*lPtr);
		*lPtr = NULL;
	}	
}

void mem_error(){
	puts("memoria esaurita");
	exit(EXIT_FAILURE);
}

int  save_int(){
	int tmp;
	scanf("%d", &tmp);
	return tmp;
}
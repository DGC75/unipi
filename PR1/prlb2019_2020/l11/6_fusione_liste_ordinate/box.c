#include <stdio.h>
#include <stdlib.h>

typedef struct intero{
	int dato;
	struct intero* next;
}Intero;

typedef Intero* ListaInteri;

void 		mem_error();
void 		add_ord(ListaInteri *lPtr);
ListaInteri fondi_lst(ListaInteri *lst_1, ListaInteri *lst_2);
void		print_lst(ListaInteri lPtr);
void 		ins_ord(ListaInteri *lPtr, int val);
Intero* 	allocNewIntero(int val);
void		free_lst(ListaInteri *lPtr);

int main(){

	ListaInteri lst_1 = NULL;
	ListaInteri lst_2 = NULL;


	add_ord(&lst_1);
	add_ord(&lst_2);

	ListaInteri lst_union = fondi_lst(&lst_1, &lst_2);
	print_lst(lst_union);

	free_lst(&lst_1);
}



ListaInteri fondi_lst(ListaInteri *lst_1, ListaInteri *lst_2){

	Intero* precPtr1 = NULL;
	Intero* corrPtr1 = *lst_1;

	Intero* corrPtr2 = *lst_2;

	if(*lst_1 == NULL)
		return *lst_2;
	

	while(*lst_2 != NULL){

		corrPtr1 = *lst_1;
		corrPtr2 = *lst_2;

		if(corrPtr2->dato <= corrPtr1->dato){
			
			*lst_2 = corrPtr2->next;
			*lst_1 = corrPtr2;
			(*lst_1)->next = corrPtr1;
			corrPtr2 = *lst_2;
			
		}
		else{
			while(corrPtr1 != NULL && corrPtr2->dato > corrPtr1->dato){
				precPtr1 = corrPtr1;
				corrPtr1 = corrPtr1->next;
			}

			*lst_2 = corrPtr2->next;
			

			corrPtr2->next = corrPtr1;
			precPtr1->next = corrPtr2;

		}
	}

	return *lst_1;
}

void free_lst(ListaInteri *lPtr){
	if(*lPtr != NULL){
		free_lst(&(*lPtr)->next);
		free(*lPtr);
		*lPtr = NULL;
	}
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
	else{
		newIntero->dato = val;
		
	}
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

void add_ord(ListaInteri *lPtr){
	
	int tmp;
	while(scanf("%d", &tmp) == 1 && tmp > -1)
		ins_ord(lPtr, tmp);
}

void mem_error(){
	puts("Memoria esaurita.");
	exit(EXIT_FAILURE);
}
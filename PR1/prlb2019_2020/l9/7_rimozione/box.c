#include <stdio.h>
#include <stdbool.h>
#include <stdlib.h>
/*#include <math.h>*/

struct elemento{
	int info;
	struct elemento* next;
};

typedef struct elemento ElementoDiLista;
typedef ElementoDiLista* ListaDiElementi;

void 			 addTopList(ListaDiElementi *lista, int v);
void 			 addBottomList(ListaDiElementi *lista, int v);
void 			 removeFirstOccurrence(ListaDiElementi *lista, int v);
void 			 get_pos_int(int *v);
void			 printList(ListaDiElementi lista); 
_Bool			 is_Even(int v);
ElementoDiLista* allocNewElement();

int main(void){

	int i = 0;
	ListaDiElementi lista = NULL;
	get_pos_int(&i);

	while(i != 0){

		if (i < 0){
			removeFirstOccurrence(&lista, i);
		}
		else if(is_Even(i)){
			addTopList(&lista, i);
		} 
		else{
			addBottomList(&lista, i);
		}

		get_pos_int(&i);
	}
	printList(lista);
		
}



void printList(ListaDiElementi lista){
	while(lista != NULL){
		printf("%d\n", lista->info);
		lista = lista->next;
	}
}

void removeFirstOccurrence(ListaDiElementi* lista, int v){
	v *= (-1);
	/*v = abs(v);*/
	ElementoDiLista* precPtr = *lista;
	while((*lista) != NULL){

		if ((*lista)->info == v){

			ElementoDiLista* tempPtr = *lista;

			if (precPtr == (*lista)){
				(*lista) = (*lista)->next;
			}
			else{
				precPtr->next = (*lista)->next;
			}
			free(tempPtr);
			return;
		}
		precPtr = *lista;
		lista = &(*lista)->next;
	}
}

void addTopList(ListaDiElementi *lista, int v){

	ElementoDiLista* newElement = allocNewElement();
	newElement->info = v;

	if((*lista) != NULL){
		newElement->next = (*lista);
	}
	(*lista) = newElement;
}	

void addBottomList(ListaDiElementi *lista, int v){

	ElementoDiLista* newElement = allocNewElement();
	newElement->info = v;

	while((*lista) != NULL){
		lista = &(*lista)->next;
	}
	(*lista) = newElement; 
}

ElementoDiLista* allocNewElement(){

	ElementoDiLista* newElement = calloc(1, sizeof(ElementoDiLista));
	if (newElement != NULL){
		return newElement;	
	}
	else{
		puts("Memoria esaurita");
		exit(EXIT_FAILURE);
	}
}

void get_pos_int(int *v){
	while(scanf("%d", v) != 1){
		puts("Input non corretto. Inserire un numero intero:");
		scanf("%*[^\n]");
		scanf("%*c");
	}
}

_Bool is_Even(int v){
	if (v%2){
		return false;
	}
	return true;
}
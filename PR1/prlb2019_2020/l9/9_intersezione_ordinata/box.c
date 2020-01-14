#include <stdio.h>
#include <stdlib.h>

#define N 2

typedef struct elemento{
	int info;
	struct elemento* next;
} Elemento;

typedef Elemento* Lista;


void 	  get_int(int *var);
void 	  insert_in_order(Lista* list, int val);
void	  inters_liste(Lista* lista1, Lista* lista2, Lista* intersezione);
void	  printList(Lista list);
int 	  binary_search(Lista list, int val);
Elemento* allocNewElement();

int main(void){

	Lista arrayDiListe[N+1]= {NULL, NULL, NULL};
	int var;
	int i;

	for (i = 0; i < N; ++i){

		get_int(&var);
		while(var >= 0){

			insert_in_order(&arrayDiListe[i], var);

			get_int(&var);
		}
	}
	inters_liste(&arrayDiListe[N-1], &arrayDiListe[N-2], &arrayDiListe[N]);
	printList(arrayDiListe[N]);

}




void inters_liste(Lista* lista1, Lista* lista2, Lista* intersezione){

	while((*lista1) != NULL){
		int temp = (*lista1)->info;

		if (binary_search(*lista2, temp)){

			insert_in_order(intersezione, temp);
		}

		lista1 = &(*lista1)->next;
	}
}

int binary_search(Lista list, int val){
	while(list != NULL){
		if (list->info == val){
			return 1;
		}
		list = list->next;
	}
	return 0;
}

void insert_in_order(Lista* list, int val){
    
	Elemento* newElement = allocNewElement(); 
	newElement->info = val;
	Elemento* precPtr = (*list);
	if ((*list) != NULL){
		
		while(val > (*list)->info && (*list)->next != NULL){
		precPtr = (*list);
		list = &(*list)->next;
		}

		if(val < (*list)->info){
			if (precPtr == (*list)){
				newElement->next = (*list);
				(*list) = newElement;
			}
			else{				
				newElement->next = (*list);
				precPtr->next = newElement;

			}
		}
		else if (val != (*list)->info && (*list)->next == NULL){
			(*list)->next = newElement;
		}
	}
	else{
		(*list) = newElement;
	}	
}

void printList(Lista list){

	if (list == NULL){
		printf("\n");
		return;
	}

	while(list != NULL){
		printf("%d\n", list->info);
		list = list->next;
	}
}

Elemento* allocNewElement(){

	Elemento* newElement = calloc(1, sizeof(Elemento));
	if (newElement != NULL){
		return newElement;
	}
	else{
		puts("Memoria esaurita");
		exit(EXIT_FAILURE);
	}
}

void get_int(int *var){

	while(scanf("%d", var)!=1){

		puts("Input non corretto. Inserisci un intero:");
		scanf("%*[^\n]");
		scanf("%*c");
	}
}
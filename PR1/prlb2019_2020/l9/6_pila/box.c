#include <stdio.h>
#include <stdlib.h>

struct elemento{

	int info;
	struct elemento * next;
};

typedef struct 	elemento 			ElementoDiLista;
typedef 		ElementoDiLista* 	ListaDiElementi;


void procedura	 (int valore, ListaDiElementi *testaLista);			
void get_int  	 (int* var);
void printList   (ListaDiElementi lista);
void push		 (ListaDiElementi *lista, int val);
void pop 		 (ListaDiElementi *lista);

int main(void){

	int i;
	get_int(&i);
	ListaDiElementi	pila = NULL;
	procedura(i, &pila);
}

void get_int(int *var){

	while(scanf("%d", var)!=1){
		puts("Input non valido. Inserisci un intero:");
		scanf("%*[^\n]");
		scanf("%*c");
	}
}

void printList(ListaDiElementi lista){

	while(lista != NULL){		
		printf("%d\n", lista->info);
		lista = lista->next;
	}
	puts("");
}

void push(ListaDiElementi *lista, int val){

	ElementoDiLista *newElemento = calloc(1, sizeof(ElementoDiLista));

	if(newElemento != NULL){
		newElemento->info = val;
		newElemento->next = *lista;
		*lista = newElemento;
	}
	else{
		puts("Memoria esaurita");
		exit(EXIT_FAILURE);
	}
}

void pop (ListaDiElementi *lista){
	if(*lista != NULL){	
		ElementoDiLista *tempPtr = *lista;
		*lista = (*lista)->next;
		free(tempPtr);
	}
}

void procedura(int valore, ListaDiElementi *testaLista){

	int i = valore;
	while(i >= 0){
		if(i != 0){
			push(testaLista, i);
			get_int(&i);		
		}
		else{
			pop(testaLista);
			get_int(&i);
		}
	}
	printList(*testaLista);
}


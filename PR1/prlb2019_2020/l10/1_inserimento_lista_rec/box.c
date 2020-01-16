#include <stdio.h>
#include <stdlib.h>

typedef struct intero{
    int dato;
    struct intero* next;
}Intero;

typedef Intero* ListaInteri;

void insert_h(ListaInteri *lPtr, int data);
void insert_negativi(ListaInteri *lPtr);
void print_lst(ListaInteri lPtr);
void mem_error();
void free_lst(ListaInteri *lPtr);

int main(void){

	int input = 0;
	ListaInteri lst = NULL;

	while(scanf("%d", &input) == 1 && input >= 0){
		insert_h(&lst, input);
	}
	insert_negativi(&lst);
	print_lst(lst);
    free_lst(&lst);

    return 0;
}

void print_lst(ListaInteri lPtr){
	while(lPtr != NULL){
		printf("%d -> ", lPtr->dato);
		lPtr = lPtr->next;
	}
	printf("NULL\n");
}

void insert_h(ListaInteri *lPtr, int input){
	Intero *newIntero = calloc(1, sizeof(Intero));

	if(newIntero == NULL)
		mem_error();

	newIntero->dato = input;
	newIntero->next = *lPtr;

	*lPtr = newIntero;

}


void free_lst(ListaInteri *lPtr){

    while((*lPtr)->next != NULL){
        free_lst(&(*lPtr)->next);
    }
    
    free(*lPtr);
    *lPtr = NULL;
}

void insert_negativi(ListaInteri *lPtr){

    ListaInteri *head = lPtr;
    ListaInteri *tail = NULL;

    if(*lPtr != NULL){
        if((*lPtr)->next != NULL){
     		tail = &(*head)->next;	
     		insert_negativi(tail);       
        }
    	if ((((*head)->dato)%2) == 0){

    		Intero *newIntero = calloc(1, sizeof(Intero));

    		if (newIntero == NULL)
    			mem_error();

    		newIntero->dato = -1;

    		newIntero->next = *head;
    		(*head) = newIntero;
    	}
    	else if(tail != NULL){
    		(*head)->next = *tail;
    		return;
    	}
    }
}

void mem_error(){
	puts("Memoria esaurita");
	exit(EXIT_FAILURE);
}

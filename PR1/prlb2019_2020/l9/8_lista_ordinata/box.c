#include <stdio.h>
#include <stdlib.h>

typedef struct element{

	int info;
	struct element* next;
} Element;

typedef Element* ElementsList;

void 	 get_int		 (int *var);
void 	 printList		 (ElementsList list);
void 	 insertInOrder	 (ElementsList *list, int val);
Element* allocNewElement (void);

int main(void){

	int i;
	ElementsList list = NULL;

	get_int(&i);

	while(i >= 0){

		/*INSERTION*/
		insertInOrder(&list, i);

		get_int(&i);
	}

	printList(list);
}


Element* allocNewElement(void){

	Element* newElement = calloc(1, sizeof(Element));

	if(newElement != NULL){

		return newElement; 

	}else{
		puts("Memoria esaurita");
		exit(EXIT_FAILURE);
	}
}

void insertInOrder(ElementsList *list, int val){

	Element* newElement = allocNewElement();
	newElement->info 	= val; 
	Element* precPtr = (*list);

	if ((*list) != NULL){

		while(val > (*list)->info && (*list)->next != NULL){

			precPtr = (*list);
			list = &(*list)->next;
		}

		if (val <= (*list)->info){

			if (precPtr == (*list)){
				newElement->next = (*list);
				(*list) = newElement;
			}
			else{
				newElement->next = (*list);
				precPtr->next = newElement;
			}
		}
		else if((*list)->next == NULL){
			
			(*list)->next = newElement;
			newElement->next = NULL;
		}
	}
	else{
		(*list) = newElement;
	}
}

void printList(ElementsList list){

	while(list != NULL){
		printf("%d\n", list->info);
		list = list->next;
	}
}

void get_int(int *var){

	while(scanf("%d", var) != 1){

		puts("Input non corretto. Inserisci un numero intero:");
		scanf("%*[^\n]");
		scanf("%*c");
	}
}


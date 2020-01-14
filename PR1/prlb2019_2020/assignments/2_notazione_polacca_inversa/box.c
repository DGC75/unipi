#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <limits.h>
#include <stdbool.h>

#define DIM 30

#define OVERFLOW_SUM_COND (op2 > 0 && (op1 > INT_MAX - op2)) || (op2 < 0 && (op1 < INT_MIN - op2)) 
#define OVERFLOW_SUBTRACT_COND (op2 > 0 && (op1 < INT_MIN + op2) ) || (op2 < 0 && op1 > INT_MAX + op2)

#define COND_1 op1 > 0 && op2 > 0 && op1 > INT_MAX/op2
#define COND_2 op1 > 0 && op2 <= 0 && op2 < INT_MIN/op1
#define COND_3 op1 <= 0 && op2 > 0 && op1 < INT_MIN/op2
#define COND_4 op1 <= 0 && op2 <= 0 && op1!=0 && op2 < INT_MAX/op1

#define OVERFLOW_MULT_COND COND_1 || COND_2 || COND_3 || COND_4

_Bool Overflow = false;

typedef struct espressione{
	char* stringa;
	struct espressione* next;
}Espressione;

typedef struct elem_pila{
	int num;
	struct elem_pila* next;
}Elem_pila;

typedef Espressione* ListaEspressioni;
typedef Elem_pila*	 Pila;

void* allocazione_sicura(int n, size_t dim_tipo);
void  insert_espressione(ListaEspressioni *list, char* stringa);
void  salva_stringa(char* buffer);
void  risolvi_lista_espressioni(ListaEspressioni* lista);
void  operazione(int op1, int op2, char operatore, Pila* pila, char** token);
void  push(Pila *pila, int num);
int   pop(Pila *pila);
void  print_Two_Complement(int num, int array[]);
void  free_lista(ListaEspressioni list);


int main(void){

	char riga[DIM];
	ListaEspressioni lista = NULL;
	salva_stringa(riga);

	while(strcmp(riga, "fine") != 0){
		insert_espressione(&lista, riga);
		salva_stringa(riga);
	}
	risolvi_lista_espressioni(&lista);
	free_lista(lista);
}

void free_lista(ListaEspressioni list){
	while((list) != NULL){
		free_lista((list)->next);
		free(list->stringa);
		free(list);
		list = NULL;
	}
}

void risolvi_lista_espressioni(ListaEspressioni* lista){

	Pila pila = NULL;
	int array[32];
	int op1, op2;

	while((*lista) != NULL){

		Overflow = false;

		char* token = strtok((*lista)->stringa, " ");		
		while(token != NULL){

			int num = strtol(token, NULL, 10);

			if ( (num > INT_MAX ) || (num < INT_MIN) ){
				Overflow = true;
				puts("Overflow!");
				token = NULL;
			}		
			else if(num == 0 && strcmp(token, "0") != 0 && !Overflow){

			/*SE IL NUMERO E' UN OPERATORE, ESEGUI CALCOLO*/
				op2 = pop(&pila);
				op1 = pop(&pila);
				operazione(op1, op2, token[0], &pila, &token);
			}
			else{
			/*E' UN NUMERO DA AGGIUNGERE ALLA PILA*/
				push(&pila, num);
				token = strtok(NULL, " ");
			}
		}
		if (!Overflow){
			printf("%d in C2: ", pila->num);
			print_Two_Complement(pila->num, array);	
			pop(&pila);
		}
		lista = &(*lista)->next;
	}
}

void print_Two_Complement(int num, int array[]){
			int k, s;
			if (num >= 0){
				for (k = 0; k < 32; ++k){
				array[k] = num%2;
				num = num/2;
				}
				for (s = 0; s <8; ++s){
					for (k = 0; k < 4; k++){
						printf("%d",array[31 - (k + 4*s)] );
					}
					printf(" ");	
				}
				puts("");
			}
			else{
				int carry = 0;
				for (k = 0; k < 32; ++k){
				array[k] = !(num%2);
					if (k == 0){
						if (array[k] == 0){
						array[k] = 1;
						}
						else{
							array[k] = 0;
							carry = 1;
						}
					}
					else{
						if(carry == 1){

							if (array[k]==0){
								array[k]=1;
								carry = 0;
							}
							else{
								array[k] = 0;
								carry = 1;
							}
						}				
				}
				num = num/2;
				}


				for (s = 0; s <8; ++s){
					for (k = 0; k < 4; k++){
						printf("%d",array[31 - (k + 4*s)] );
					}
					printf(" ");	
				}
				puts("");
			}			
}

void insert_espressione(ListaEspressioni* list, char* stringa){

	/*ALLOCA UNA STRUCT ESPRESSIONE*/
	/*ALLOCA UNA STRINGA DELLE DIMENSIONI DI stringa*/
	/*SALVA IL PUNTATORE NELLA STRUCT*/

	Espressione* newElement = allocazione_sicura(1, sizeof(Espressione));

	newElement->stringa = allocazione_sicura(1, (strlen(stringa)+1)*sizeof(char));
	strcpy(newElement->stringa, stringa);

	while((*list) != NULL){
		list = &(*list)->next;
	}
	(*list) = newElement;
}

void operazione(int op1, int op2, char operatore, Pila* pila, char** token){
	/*Esegui operazione indicata*/
	/*Se l'operazione non va in overflow, fai pop e push vari*/
	/*Se l'operazione va in overflow, stampa overflow*/
	int result=0;

	switch(operatore){
		case '+':
			/*ADDIZIONE SICURA*/
			if (OVERFLOW_SUM_COND){
				Overflow = true;
				puts("Overflow!");
				(*token) = NULL;
			}
			else{
				result = op1 + op2;
				push(pila, result);
				(*token) = strtok(NULL, " ");
			}
		break;
		case '-':
			/*SOTTRAZIONE SICURA*/
			if (OVERFLOW_SUBTRACT_COND){
				Overflow = true;
				puts("Overflow!");
				(*token) = NULL;
			}
			else{
				result = op1 - op2;
				push(pila, result);
				(*token) = strtok(NULL, " ");
			}
		break;
		case '*':
			/*MOLTIPLICAZIONE SICURA*/
			if (OVERFLOW_MULT_COND){
				Overflow = true;
				puts("Overflow!");
				(*token) = NULL;
			}
			else{
				result = op1 * op2;
				push(pila, result);
				(*token) = strtok(NULL, " ");
			}
		break;
	}
}

void push(Pila* pila, int num){
	Elem_pila* newElement = allocazione_sicura(1, sizeof(Elem_pila) );
	newElement->num = num;
	newElement->next = (*pila);
	(*pila) = newElement;
}

int pop(Pila *pila){
	Elem_pila* tempPtr = (*pila);
	int temp_num = tempPtr->num;
	(*pila) = (*pila)->next;
	free(tempPtr);
	return temp_num;
}

void* allocazione_sicura(int n, size_t dim_tipo){
	void* tempPtr = calloc(n, dim_tipo);
	if (tempPtr != NULL){
		return tempPtr;
	}
	else{
		puts("Memoria esaurita");
		exit(EXIT_FAILURE);
	}
}

void salva_stringa(char* buffer){

	fgets(buffer, DIM, stdin);
	buffer[strlen(buffer)-1] = '\0';	
}
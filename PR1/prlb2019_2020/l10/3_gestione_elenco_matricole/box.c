#include <stdio.h>
#include <stdlib.h>


typedef struct intero{
	int dato;
	struct intero* next;
}Intero;

typedef Intero* ListaInteri; 


void add_end(ListaInteri *lPtr);
void insert_end(ListaInteri *lPtr, int val);
int  recLength(ListaInteri lPtr, int acc);
void RecStampaInversa(ListaInteri lPtr, int length);
void save_int(int *val);
void delete_mult(int n, ListaInteri *lPtr);
void delete_h(ListaInteri *lPtr);
void RecStampa(ListaInteri lPtr);
void get_matr_odd_even(int *dispari, int *pari, ListaInteri lPtr);
void mem_error();

int main(){
	ListaInteri ANONIMI = NULL;

	add_end(&ANONIMI);

	int length = recLength(ANONIMI, 0);
	puts("Stampa l'elenco in ordine inverso di immissione (NULL se vuota):");
	RecStampaInversa(ANONIMI, length);
	puts("Inserisci il numero richiesto:");
	int n;
	save_int(&n);

	delete_mult(n, &ANONIMI);
	puts("Stampa l'elenco in ordine di immissione (NULL se vuota):");	
	RecStampa(ANONIMI);

	int fst_dispari = -1;
	int fst_pari = -1;

	get_matr_odd_even(&fst_dispari, &fst_pari, ANONIMI);

	printf("Dispari:%d\n", fst_dispari);
	printf("Pari:%d\n", fst_pari);
}

void add_end(ListaInteri *lPtr){

	int input;
	save_int(&input);

	while(input != 0){
		insert_end(lPtr, input);
		save_int(&input);
	}

}

void insert_end(ListaInteri *lPtr, int val){

	Intero *newIntero = calloc(1, sizeof(Intero));
	if(newIntero == NULL)
		mem_error();

	newIntero->dato = val;

	if (*lPtr == NULL){
		*lPtr = newIntero;		
	}
	else{
		
		while((*lPtr)->next != NULL)
			lPtr = &(*lPtr)->next;

		(*lPtr)->next = newIntero;
	}
}

int  recLength(ListaInteri lPtr, int acc){
	if (lPtr == NULL)
		return acc;
	else{
		return recLength(lPtr->next, acc+1); 
	}
}

void RecStampaInversa(ListaInteri lPtr, int length){
	static acc;
	if(lPtr != NULL){
		RecStampaInversa(lPtr->next, length);
		printf("%d->", lPtr->dato);
		acc++;
	}
	if(acc == length)
		puts("NULL");
}


void save_int(int *val){

	while(scanf("%d", val) != 1 || *val < 0 ){
		puts("Inserisci intero positivo o 0 per uscire");
		scanf("%*[^\n]");
	}

}
void delete_mult(int n, ListaInteri *lPtr){
	if(*lPtr != NULL){
		if(((*lPtr)->dato%n) == 0){
			delete_h(lPtr);
			delete_mult(n, lPtr);
		}
		else{
			delete_mult(n, &(*lPtr)->next);
		}
	}
}

void delete_h(ListaInteri *lPtr){
	
	Intero *tmpPtr = *lPtr;
	*lPtr = (*lPtr)->next;
	free(tmpPtr);
	tmpPtr = NULL;
}

void RecStampa(ListaInteri lPtr){

	if (lPtr != NULL){
		printf("%d->", lPtr->dato);
		RecStampa(lPtr->next);
		return;
	}
	puts("NULL");
}
void get_matr_odd_even(int *odd, int *even, ListaInteri lPtr){
	if (lPtr != NULL){
		if (*odd == -1 && (lPtr->dato %2 == 1)){
			*odd = lPtr->dato;
			get_matr_odd_even(odd, even, lPtr->next);
		}
		if (*even == -1 && (lPtr->dato %2 == 0)){
			*even = lPtr->dato;
			get_matr_odd_even(odd, even, lPtr->next);
		}
	}
}
void mem_error(){

	puts("Memoria esaurita");
	exit(EXIT_FAILURE);
}
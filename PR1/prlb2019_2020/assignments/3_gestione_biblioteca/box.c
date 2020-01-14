#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define DIM 	100
#define OPTIONS 5


typedef struct libro{
	int isbn;
	char title[DIM];
	char author[DIM];
	int tot_copies;
	int	available;
	struct libro* next;
}Libro;

typedef Libro* CatalogoLibri;


void inserimento_ordinato(Libro* tmpBook, CatalogoLibri* catalogo);
void printList(CatalogoLibri list);
void dealloc_catalogo(CatalogoLibri catalogo);
void printMenu(void);
void chiedi_scelta(int* scelta);
void cercaLibro(CatalogoLibri list, char author[], char title[]);
void find(CatalogoLibri list, char* author, char* book);
void presta (CatalogoLibri list,int isbn);
void restituisci(CatalogoLibri list,int isbn);
void saluto(void);


void stampa_catalogo (CatalogoLibri list);
void cerca (CatalogoLibri list);
void prestito (CatalogoLibri list);
void restituzione (CatalogoLibri list);
void esci (CatalogoLibri list);

int main(void){
	atexit(saluto);
	CatalogoLibri catalogo = NULL;
	Libro* tmpBook = calloc(1, sizeof(Libro));

	scanf("%d,%[^,],%[^\n]", &(tmpBook)->isbn, tmpBook->title, tmpBook->author);
	while(tmpBook->isbn > 0){
		tmpBook->tot_copies = 1;
		inserimento_ordinato(tmpBook, &catalogo);
		scanf("%d,%[^,],%[^\n]", &(tmpBook)->isbn, tmpBook->title, tmpBook->author);
	}
	free(tmpBook);
	tmpBook = NULL;
	int scelta = 0;
	void (*menu [OPTIONS]) (CatalogoLibri) = {stampa_catalogo, cerca, prestito, restituzione, esci};
	
	chiedi_scelta(&scelta);	
	
	while(scelta > 0 && scelta < OPTIONS + 1){	
		menu[scelta-1](catalogo);		
		chiedi_scelta(&scelta);		
	}
	
	dealloc_catalogo(catalogo);
}

void chiedi_scelta(int* scelta){
	printMenu();		
	while(scanf("%d", scelta) !=1 || *scelta < 1 || *scelta > 5){
		puts("Errore. Scelta non valida.");
		scanf("%*[^\n]");
		scanf("%*c");						
	}	
}

void printMenu(){
	puts("Scegli un opzione:");
	puts("1) Stampa catalogo.");
	puts("2) Cerca.");
	puts("3) Prestito.");
	puts("4) Restituzione.");
	puts("5) Esci.");
	printf("Scelta:  ");			
}

void printList(CatalogoLibri list){
	while(list != NULL){
		printf("%d\t%-70s\t%-30s%-d\n", list->isbn, list->title, list->author, list->tot_copies);
		list = list->next;
	}
}

void inserimento_ordinato(Libro* tmpBook, CatalogoLibri* catalogo){

	Libro* precPtr = NULL;
	Libro* corrPtr = (*catalogo);

	if ((*catalogo) != NULL){

		while(corrPtr != NULL && strcmp(tmpBook->author, corrPtr->author) > 0){
			precPtr = corrPtr;
			corrPtr = corrPtr->next;
		}

	
		while(corrPtr != NULL && strcmp(tmpBook->title, corrPtr->title) > 0 && strcmp(tmpBook->author, corrPtr->author) == 0){		
			precPtr = corrPtr;
			corrPtr = corrPtr->next;					
		}

		
		if (corrPtr != NULL && strcmp(tmpBook->title, corrPtr->title) == 0){
			corrPtr->available += 1;
			corrPtr->tot_copies += 1;
		}
		else{

			Libro* newBook = calloc(1, sizeof(Libro));
			if (newBook != NULL){	

				(*newBook) = (*tmpBook);
				newBook->tot_copies = newBook->available = 1;
	

				if (precPtr != NULL){
					precPtr->next = newBook;
					newBook->next = corrPtr;
				}
				else{
					(*catalogo) = newBook;
					newBook->next = corrPtr;
				}

			}
			else{
				puts("Memoria esaurita");
				exit(EXIT_FAILURE);
			}
		}
	}
	else{
		Libro* newBook = calloc(1, sizeof(Libro));
		if (newBook != NULL){
			(*newBook) = (*tmpBook);
			newBook->available = newBook->tot_copies = 1;
			newBook->next = NULL;
			(*catalogo) = newBook;
		}
		else{
			puts("Memoria esaurita");
			exit(EXIT_FAILURE);
		}
	}
}

void dealloc_catalogo(CatalogoLibri catalogo){
	while(catalogo != NULL){
		dealloc_catalogo(catalogo->next);
		free(catalogo);
		catalogo = NULL;
	}
}

void stampa_catalogo(CatalogoLibri list){
	while(list != NULL){
		printf("%d - %s - %s (%d/%d)\n", list->isbn, list->author, list->title, list->available, list->tot_copies);
		list = list->next;
	}	
}

void cerca(CatalogoLibri list){

	char author[DIM];
	char book[DIM];

	scanf("%*[^\n]");
	scanf("%*c");
	printf("Inserire nome autore: ");
	fgets(author, DIM, stdin);
	author[strlen(author)-1] = '\0';
	printf("Inserire titolo: ");
	fgets(book, DIM, stdin);	
	book[strlen(book)-1] = '\0';

	find(list, author, book);	
}

void find(CatalogoLibri list, char author[], char book[]){
	if(list != NULL && strcmp(author, list->author) != 0 ){
		find(list->next, author, book);
		return;
	}
	if (list == NULL){
		puts("Libro non trovato.");
	} 
	else{
		while(list != NULL && strcmp(book, list->title) != 0){
			return find(list->next, author, book);
		}
		if (list == NULL){
			puts("Libro non trovato.");
		}
		else{
			if (list->available > 0){
				printf("%d copie disponibili.\n",list->available );
			}
			else{
				puts("Non ci sono copie disponibili del libro richiesto.");
			}
		} 	
	}
}

void prestito (CatalogoLibri list){

	int isbn;

	printf("ISBN: ");
	scanf("%*[^\n]");
	scanf("%*c");
	scanf("%d", &isbn);

	presta(list ,isbn);
}

void presta (CatalogoLibri list,int isbn){
	while(isbn != list->isbn && list!= NULL){
		list = list->next;
	}
	if (list == NULL){
		puts("Libro non trovato.");
	}
	else{
		if (list->available > 0){
			list->available -= 1;
			puts("Operazione completata.");
		}
		else{
			puts("Non ci sono copie disponibili del libro richiesto.");
		}
	}
}

void restituzione (CatalogoLibri list){

	int isbn;

	printf("ISBN: ");
	scanf("%*[^\n]");
	scanf("%*c");
	scanf("%d", &isbn);

	restituisci(list, isbn);
}

void restituisci(CatalogoLibri list,int isbn){

	while(isbn != list->isbn && list!= NULL){
		list = list->next;
	}
	if (list == NULL){
		puts("Libro non trovato.");
	}
	else{
		if (list->available != list->tot_copies){
			list->available += 1;
			puts("Operazione completata.");
		}
		else{
			puts("Non risultano copie in prestito.");
		}
	}	
}

void esci (CatalogoLibri list){

	dealloc_catalogo(list);
	exit(EXIT_SUCCESS);
}

void saluto(void){
	puts("Bye");
}
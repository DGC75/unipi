#include <stdio.h>
#include <stdlib.h>
#include <string.h>

/*DEFINIZIONI DI DATI*/
typedef struct studente{
	char 	nome[10];
	char 	cognome[10];
	int 	voto;
	struct studente *nextStud;
} Studente;

typedef Studente *ListaStudenti;

/*DICHIARAZIONI DI FUNZIONI*/
void insert(ListaStudenti *lista, char *nome, char *cognome, int voto);
void printIfPassed(Studente stud);
int is_Empty(ListaStudenti lista);
void stampa_lista(ListaStudenti lista);
void stampa_sufficienti(ListaStudenti lista);

/*MAIN*/
int main(void){
	ListaStudenti lista=NULL;
	FILE *fPtr;
	if ((fPtr= fopen("input.txt", "r"))==NULL){
		puts("impossibile aprire file");
	}else{
		if (fPtr==NULL){
			puts("Memoria esaurita");
			exit(EXIT_FAILURE);
		}
		while(!feof(fPtr)){
			char nome[10];
			char cognome[10];
			int  voto;

			fscanf(fPtr,"%[^;];%[^;];%d\n", cognome, nome, &voto);
			insert(&lista, nome, cognome, voto);
		}
	}
	stampa_sufficienti(lista);
}


/*DEFINIZIONI DI FUNZIONI*/
void insert(ListaStudenti *lista, char *nome, char *cognome, int voto){
	ListaStudenti newStud=calloc(1,sizeof(Studente));
	if (newStud!=NULL){
		/*INIT NODO*/
		strcpy(newStud->nome, nome);
		strcpy(newStud->cognome, cognome);
		newStud->voto=voto;
		newStud->nextStud = NULL;
		

		ListaStudenti precStud = NULL;
		ListaStudenti corrStud = *lista;
		
		while(corrStud != NULL){
			precStud = corrStud;
			corrStud = corrStud->nextStud;
		}

		if (precStud == NULL){
			/*INSERIMENTO ALL'INIZIO DELLA LISTA*/
			newStud->nextStud= *lista;
			*lista= newStud;
		}else{
			/*INSERIMENTO TRA DUE NODI*/
			precStud->nextStud=newStud;
			newStud->nextStud=corrStud;
		}
	
	}else{
		puts("Memoria esaurita");
		exit(EXIT_FAILURE);
	}
}

int is_Empty(ListaStudenti lista){
	return lista==NULL;	
}

void stampa_lista(ListaStudenti lista){
	if (is_Empty(lista)){
		puts("Lista vuota");
	}else{
		puts("");
		printf("Nome\t\tCognome\t\tVoto\n\n");
		while(lista!=NULL){
			printf("%-15s %-6s\t\t%d\n", lista->nome, lista->cognome, lista->voto);
			lista=lista->nextStud;
		}
		puts("");
	}
}

void printIfPassed(Studente stud){
	if (stud.voto >=18){
		printf("%10s%10s  %d ESAME SUPERATO\n", stud.cognome, stud.nome, stud.voto);
	}
}

void stampa_sufficienti(ListaStudenti lista){
	while(lista!=NULL){
		printIfPassed(*lista);
		lista=lista->nextStud;
	}
}


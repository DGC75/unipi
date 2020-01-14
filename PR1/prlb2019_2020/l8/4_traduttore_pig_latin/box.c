#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>


#define DIM_MENU 4
#define MAX_WORD_LENGTH 15
#define MAX_WORDS_PER_STRING_LENGTH 6
#define MAX_STRING_LENGTH MAX_WORDS_PER_STRING_LENGTH*(MAX_WORD_LENGTH +1)



void inserisci_nuova_frase(char array[MAX_STRING_LENGTH]);
void visualizza_in_maiuscole(char array[MAX_STRING_LENGTH]);
void traduci_frase(char array[MAX_STRING_LENGTH]);
void esci(char array[MAX_STRING_LENGTH]);



void strupr(char* stringa, char* memoria);
void strlwr(char* string, char* memoria);
char* en2piglatin(char*);
void saluto();



int main(){
	atexit(saluto);

	void (*f[DIM_MENU])(char array[MAX_STRING_LENGTH]) = {
		inserisci_nuova_frase,
		visualizza_in_maiuscole,
		traduci_frase,
		esci
	};
	int i;

	while(1){
		printf("Scegliere l'operazione:");
		while(scanf("%d", &i)!=1 || i<1 || i>DIM_MENU){
			printf("Scegliere l'operazione:");
			scanf("%*[^\n]");
			scanf("%*c");
		}
		char stringa_utente[MAX_STRING_LENGTH];
		f[i-1](stringa_utente);
	}
}


void inserisci_nuova_frase(char stringa_utente[MAX_STRING_LENGTH]){

	printf("\nInserire stringa:\n");
	scanf("%*[^\n]");
	scanf("%*c");

	/*IL SEGUENTE PEZZO DI CODICE E' STATO GENTILMENTE SCOPIAZZATO DA QUI*/
	/*https://stackoverflow.com/questions/1247989/how-do-you-allow-spaces-to-be-entered-using-scanf*/

	/*PRENDE LA STRINGA*/
	fgets(stringa_utente,MAX_STRING_LENGTH,stdin);
	/*RIMUOVE IL NEWLINE FINALE*/
	if (strlen(stringa_utente)>0){
		stringa_utente[strlen(stringa_utente)-1]= '\0';

	}
	/*FINE DEL PEZZO SCOPIAZZATO*/

}

void visualizza_in_maiuscole(char stringa_utente[MAX_STRING_LENGTH]){
		printf("\n");
		int lunghezza=strlen(stringa_utente);
		char array[lunghezza+1];
		array[lunghezza]='\0';
		strupr(stringa_utente, array);
		printf("%s",array);
		printf("\n");
}

char* en2piglatin(char* parola){
	int maiusc=0;
	char* vocali_pure="aeiouAEIOU";
	char* consonanti_pure="bcdfghjklmnpqrstvwxyzBCDFGHJKLMNPQRSTVWXYZ";
	char* vocali_secondarie="aeiouyAEIOUY";
	char* consonanti_secondarie="bcdfghjklmnpqrstvwxzBCDFGHJKLMNPQRSTVWXZ";
	if (isupper(parola[0])){
		maiusc=1;
	}else{
		maiusc=0;
	}
	/*SE LA PRIMA LETTERA È UNA VOCALE...*/
	if(strchr(vocali_pure,(int) parola[0])!=NULL){
		strcat(parola,"way");
		return parola;
	}else if(strchr(consonanti_pure,(int) parola[0])!=NULL){
	/*SE LA PRIMA LETTERA È UNA CONSONANTE...*/
	/*SALVA LA STRINGA PRIMA DELLA PRIMA VOCALE IN UN ARRAY TEMPORANEO*/
	/*CALCOLA LA LUNGHEZZA DELLA STRINGA PRIMA DELLA VOCALE*/
	size_t length_orig=strlen(parola);
	char stringa_temporanea[length_orig+1];
	/*CONTROLLIAMO LA PAROLA CARATTERE PER CARATTERE E SE IL CARATTERE VA BENE, SALVIAMOLO IN STRINGA TEMPORANEA*/
	char *ptr=parola;
	int i=0;
	stringa_temporanea[i]= *ptr;
	for (i = 1; (i < length_orig+1) && (ptr!=NULL); ++i){
		++ptr;
		if ( strchr(consonanti_secondarie,*ptr)!=NULL){
			stringa_temporanea[i]=*ptr;
		} else{
			stringa_temporanea[i]='\0';
			ptr=NULL;
		}
	}
	/*PRENDI IL RESTO DELLA STRINGA E SOVRASCRIVILO ALLA PAROLA, AGGIUNGENDO '\0'*/
	ptr=++parola;
	/*RITORNAMI LA PRIMA OCCORRENZA DI UNA VOCALE SECONDARIA IN PAROLA*/
	ptr=strpbrk(parola,vocali_secondarie);
	parola=ptr;
	
	strcat(parola, stringa_temporanea);
	strlwr(parola,parola);
	strcat(parola, "ay");
	if (maiusc==1){
		parola[0]=toupper(parola[0]);
	}
	return parola;
	}else{
	/*SE NON È UNA DELLE PRECEDENTI...*/
		return parola;
	}
	return "Qualcosa e' andato storto...molto storto.";
}

void traduci_frase(char stringa_utente[MAX_STRING_LENGTH]){
	printf("\n");
	int num_of_words=0;
	char stringa_smontata[MAX_WORDS_PER_STRING_LENGTH][MAX_WORD_LENGTH];
	char stringa_tradotta[MAX_STRING_LENGTH+ MAX_WORDS_PER_STRING_LENGTH*3]={0};
	char *token;
	token=strtok(stringa_utente," ");
	int i=0;
	strcpy(stringa_smontata[i],token);

	for (i = 1; (token!=NULL) && (i < MAX_WORDS_PER_STRING_LENGTH); ++i){
		token=strtok(NULL," ");
		if (token!=NULL){
			strcpy(stringa_smontata[i],token);
		}
		num_of_words=i;
	}
	int j;
	for (j = 0; j < num_of_words; ++j){
		strcat(stringa_tradotta,en2piglatin(stringa_smontata[j]));
		strcat(stringa_tradotta," ");
	}

	/*TODO: SOSTITUIRE L'ULTIMO SPAZIO CON \0*/
	if (strlen(stringa_tradotta)>0){
	stringa_tradotta[strlen(stringa_tradotta)-1]= '\0';
	}
	printf("%s\n",stringa_tradotta);
}

void esci(char array[MAX_STRING_LENGTH]){

	exit(EXIT_SUCCESS);
}

void saluto(){
	printf("\n");
	printf("Ciao!\n");
}

void strupr(char* string, char* memoria){
	int size= strlen(string)+1;
	int i;
	for (i = 0; i < size; ++i){
		memoria[i]=toupper(string[i]);
	}
}
void strlwr(char* string, char* memoria){
	int size= strlen(string)+1;
	int i;
	for (i = 0; i < size; ++i){
		memoria[i]=tolower(string[i]);
	}
}

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

#define DIM 36

int morseValue(char c);
int parole_per_stringa(char* riga);

int main(void){
	/*APERTURA DEL FILE IN LETTURA*/
	FILE *fPtr = fopen("input.txt","r");
	if (fPtr != NULL){

		/*DICHIARAZIONE TABELLA CARATTERI E BUFFER VARI*/
		char tabella[DIM][10];
		char riga[118];
		char carattere = '\0';
		char *nonAlNumchars = "$\"#%&\'()*+-,./:;<=>!?@[\\]^_`{}|~";

		int i;	
		int j; 
		/*ACQUISIZIONE TABELLA TRADUZIONE CARATTERI*/
		for (i = 0; i < DIM; ++i){
			fscanf(fPtr, "%c:%[^\n]\n", &carattere, riga);
			strcpy(tabella[i],riga);
		}
		fscanf(fPtr, "****\n");

		/*TRADUZIONE RIGHE*/

		/*LEGGE RIGA PER RIGA*/
		fgets(riga, 118, fPtr);
		while(!feof(fPtr)){
			riga[strlen(riga)-1] = '\0';
			if (strpbrk(riga, nonAlNumchars) == NULL){

			int num_parole_per_frase= parole_per_stringa(riga);

				/*LEGGE PAROLA PER PAROLA*/
				char *token = strtok(riga," ");

					/*TRADUCE E STAMPA PAROLA PER PAROLA, CON SPAZIATURA ADEGUATA*/
					for (i = 0; i < num_parole_per_frase-1; ++i){

						/*TRADUCE E STAMPA CARATTERE PER CARATTERE, CON SPAZIATURA ADEGUATA*/	
						for (j = 0; j < strlen(token)-1; ++j){
							printf("%s   ",tabella[morseValue(token[j])]);
						}
						printf("%s       ", tabella[morseValue( token[j] )]);
						token = strtok(NULL, " ");

					}
					if (token != NULL){
						for (j = 0; j < strlen(token)-1; ++j){
							printf("%s   ",tabella[morseValue(token[j])]);
						}
					}
					printf("%s\n", tabella[morseValue(token[j])]);
				fgets(riga, 118, fPtr);
			}
			else{
				puts("Errore nell'input");	
				fgets(riga, 118, fPtr);			
			}
		}
	fclose(fPtr);
	}
	else{
		puts("Impossibile aprire file");
		exit(EXIT_FAILURE);
	}		
}


int morseValue(char c){
	if (isalpha(c)){
		/*RITORNO INDICE CARATTERE ALFABETICO*/
		if(islower(c)){
			return c%97;
		}
		else{
			return c%65;
		}
	}
	else{
		/*RITORNO INDICE CARATTERE NUMERICO*/
		return 26 + c%48;
	}
}

int parole_per_stringa(char* riga){
	/*DOVREBBE CONTARE IL NUMERO DI PAROLE PRESENTE IN UNA STRINGA (DOVREBBE...)*/
	int i;
	int count=0;
	for (i = 0; i < strlen(riga); ++i){
		if (riga[i] == ' '){
			++count;
		}		
	}
	return ++count;
}
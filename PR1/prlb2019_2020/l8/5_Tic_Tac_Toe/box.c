#include <stdio.h>
#include <string.h>
#include <stdlib.h>

#define DIM 3

/*void printMatrix(char matrix[][DIM], size_t dim);*/
void loadMatrix(char matrix[][DIM], size_t dim);
void checkMatrix(char matrix[][DIM]);


void checkRiga(char tessera_centrale,char matrix[][DIM], size_t row, size_t col);
void checkColonna(char tessera_centrale,char matrix[][DIM], size_t row, size_t col);
void checkDiagonali(char tessera_centrale,char matrix[][DIM]);
void checkCentrale(char tessera_centrale,char matrix[][DIM]);


int main(void){
	/*printMatrix(matrix, DIM);*/
	char matrix[DIM][DIM];
	loadMatrix(matrix, DIM);
	checkMatrix(matrix);
	return 0;
}



void loadMatrix(char matrix[][DIM], size_t dim){
	char riga[DIM*2];
	char *symbol_ptr;
	
	int i,j;
	for (i = 0; i < dim; ++i){
		/*ACQUISIZIONE RIGA*/
		fgets(riga,6,stdin);
		scanf("%*[^\n]");
		scanf("%*c");
		/*TOKENIZZAZIONE RIGA E ASSEGNAMENTO ALLA MATRICE*/
		symbol_ptr=strtok(riga," ");
		j=0;
		while(symbol_ptr!=NULL){
			*(*(matrix+i)+j)= *symbol_ptr;
			symbol_ptr=strtok(NULL," ");
			++j;
		}
	}	
}

void checkMatrix(char matrix[][DIM]){

	char tessera_centrale=*(*(matrix+1)+1);
	/*CONTROLLO A STELLA*/
	if (tessera_centrale!='-'){
		checkCentrale(tessera_centrale, matrix);
	}

	/*CONTROLLO COLONNE*/

	/*COLONNA SINISTRA*/
	tessera_centrale=*(*(matrix+1));	
	if (tessera_centrale!='-'){
		checkColonna(tessera_centrale, matrix, 1, 0);
	}
	/*COLONNA DESTRA*/
	tessera_centrale=*(*(matrix+1)+2);	
	if (tessera_centrale!='-'){
		checkColonna(tessera_centrale, matrix, 1, 2);
	}

	/*CONTROLLO RIGHE*/

	/*RIGA ALTA*/
	tessera_centrale=*(*(matrix)+1);	
	if (tessera_centrale!='-'){
		checkRiga(tessera_centrale, matrix, 0, 1);
	}

	/*RIGA BASSA*/
	tessera_centrale=*(*(matrix+2)+1);	
	if (tessera_centrale!='-'){
		checkRiga(tessera_centrale, matrix, 2, 1);
	}

	puts("pareggio");
	exit(0);
}

void checkCentrale(char tessera_centrale,char matrix[][DIM]){

	checkDiagonali(tessera_centrale, matrix);
	checkRiga(tessera_centrale, matrix, 1, 1);
	checkColonna(tessera_centrale, matrix, 1, 1);

}

void checkDiagonali(char tessera_centrale,char matrix[][DIM]){
	int counter=1;
	/*CHECK DIAGONALE SINISTRA*/
	char fakePtr=*(*(matrix));
	if ( fakePtr!='-' && fakePtr==tessera_centrale){
		counter++;
	}
	fakePtr=*(*(matrix+2)+2);
	if ( fakePtr!='-' && fakePtr==tessera_centrale){
		counter++;
	}
	if (counter==3){
		printf("vince %c\n",tessera_centrale);
		exit(0);
	}

	/*CHECK DIAGONALE DESTRA*/
	counter=1;
	fakePtr=*(*(matrix)+2);
	if ( fakePtr!='-' && fakePtr==tessera_centrale){
		counter++;
	}
	fakePtr=*(*(matrix+2));
	if ( fakePtr!='-' && fakePtr==tessera_centrale){
		counter++;
	}
	if (counter==3){
		printf("vince %c\n",tessera_centrale);
		exit(0);
	}	
}

void checkRiga(char tessera_centrale,char matrix[][DIM], size_t row, size_t col){
	int counter=1;
	/*CHECK CASELLA SINISTRA E DESTRA ADIACENTI*/
	char fakePtr= *(*(matrix+row)+col-1);

	if ( fakePtr!='-' && fakePtr==tessera_centrale){
		counter++;
	}
	fakePtr= *(*(matrix+row)+col+1);
	if ( fakePtr!='-' && fakePtr==tessera_centrale){
		counter++;
	}
	if (counter==3){
		printf("vince %c\n",tessera_centrale);
		exit(0);
	}
}

void checkColonna(char tessera_centrale,char matrix[][DIM], size_t row, size_t col){
	int counter=1;
	/*CHECK CASELLA SOPRA E SOTTO ADIACENTI*/
	char fakePtr= *(*(matrix+row-1)+col);

	if ( fakePtr!='-' && fakePtr==tessera_centrale){
		counter++;
	}
	fakePtr= *(*(matrix+row+1)+col);
	if ( fakePtr!='-' && fakePtr==tessera_centrale){
		counter++;
	}
	if (counter==3){
		printf("vince %c\n",tessera_centrale);
		exit(0);
	}
}


/*
void printMatrix(char matrix[][DIM], size_t dim){
	size_t i,j;
	for (i = 0; i < dim; ++i){
		for (j = 0; j < DIM-1; ++j){
			printf("%c ",*(*(matrix + i)+j) );
		}
		printf("%c\n", *(*(matrix+i)+DIM-1) );
	}
}
*/
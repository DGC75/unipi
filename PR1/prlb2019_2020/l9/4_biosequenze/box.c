#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define LUN_LINEA 101

int main(void){

	FILE *fPtr;
	fPtr = fopen("input.txt", "r");
	if (fPtr != NULL){

		int num_sequenze	= 0;
		int num_nucleotidi	= 0;
		int seq_massima		= 0;

		while(!feof(fPtr)){

			char riga[LUN_LINEA];
			fgets(riga, LUN_LINEA, fPtr);
			int length_seq = 0;

				while(riga[0] != '>' && !feof(fPtr) ){

					length_seq += (strlen(riga)-1);
					fgets(riga, LUN_LINEA, fPtr);

				}

				num_nucleotidi += length_seq;

				if( riga[0] != '\n' && !feof(fPtr) ){

					if (length_seq > seq_massima){

						seq_massima = length_seq;
					}

					num_sequenze++;
				}

		}

		printf("Numero sequenze: %d\n", num_sequenze);
		printf("Lunghezza della sequenza più lunga: %d\n", seq_massima);
		printf("Numero totale di nucleotidi: %d\n", num_nucleotidi);

	}else{

		puts("Impossibile aprire file");
		exit(EXIT_FAILURE);

	}
}
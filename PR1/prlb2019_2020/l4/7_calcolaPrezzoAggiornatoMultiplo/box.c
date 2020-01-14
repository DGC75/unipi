#include <stdio.h>

/*printf("%20s\t%20s\t%20s\n","Prezzo_Init","Percentuale","Prezzo_scontato");*/

void prezzoAggiornato(int scelta,float prezzo,int percentuale);

int main (void){
int scelta=0;
float prezzo=0;
int percentuale=0;


	while(scanf("%d", &scelta)!=1 || scelta>1){
		printf("scelta non valida\n");
		scanf("%*[^\n]");
		}
	while(scelta>=0){

		while(scanf("%f", &prezzo)!=1 || prezzo<0){
			printf("Prezzo non valido\n");
			scanf("%*[^\n]");

		}
		while(scanf("%d", &percentuale)!=1 || percentuale<0 || percentuale>100){
			printf("Percentuale non valida\n");
			scanf("%*[^\n]");
		}

		prezzoAggiornato(scelta,prezzo, percentuale);

		while(scanf("%d", &scelta)!=1 || scelta>1){
		printf("scelta non valida\n");
		scanf("%*[^\n]");
		}
	}
	/*END MAIN*/
}

void prezzoAggiornato(int scelta, float prezzo,int percentuale){
	switch(scelta){
		/*SCONTO*/
		case 0:
		printf("%20s\t%20s\t%20s\n","Prezzo_Init","Percentuale","Prezzo_scontato");
		printf("%20.2f\t%20.2f\t%20.2f\n",prezzo,(float)percentuale,prezzo*(100-percentuale)/100);
		break;
		/*IVA*/
		case 1:
		printf("%20s\t%20s\t%20s\n","Prezzo_Init","Percentuale","Prezzo_ivato");
		printf("%20.2f\t%20.2f\t%20.2f\n",prezzo,(float)percentuale,prezzo*(100+percentuale)/100);
		break;
	}
}
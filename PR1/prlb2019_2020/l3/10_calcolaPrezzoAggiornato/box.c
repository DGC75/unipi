#include <stdio.h>




int main(void){
	enum selezione {SCONTO, IVA};
	enum selezione scelta;
	int prezzoInit=0;
	int percentuale=0;

    /*ACQUISIZIONE E CONTROLLO INPUT*/

    /*CONTROLLO SCELTA*/
	scanf("%d", &scelta);
	if (scelta!=SCONTO && scelta!=IVA){
		printf("invalid input\n");
		return 0;
	}

	/*CONTROLLO PREZZO INIZIALE*/
	scanf("%d", &prezzoInit);
	if (prezzoInit<0){
		printf("invalid input\n");
		return 0;
	}

	/*CONTROLLO PERCENTUALE*/
	scanf("%d", &percentuale);
	if (percentuale<0 || percentuale>100){
		printf("invalid input\n");
		return 0;
	}
	
	/*CALCOLO E STAMPA OUTPUT*/
    switch(scelta){
    	case SCONTO:
    	printf("%20s\t%20s\t%20s\n","Prezzo_Init", "Percentuale", "Prezzo_scontato");
    	printf("%20.2f\t%20.2f\t%20.2f\n",(float)prezzoInit, (float)percentuale, (float) prezzoInit-prezzoInit*percentuale/100);
    	break;
    	case IVA:
    	printf("%20s\t%20s\t%20s\n","Prezzo_Init", "Percentuale", "Prezzo_ivato");
    	printf("%20.2f\t%20.2f\t%20.2f\n",(float)prezzoInit, (float)percentuale, (float) prezzoInit+prezzoInit*percentuale/100);
    	break;
    }    


}
#include <stdio.h>

int leggi_scelta(void);
float leggi_prezzo(void);
int leggi_percentuale(void);
void calcola_prezzo_scontato(float prezzo, int percentuale);
void calcola_prezzo_ivato(float prezzo, int percentuale);


int main(void){
	int scelta=leggi_scelta();
	int prezzo;
	int percentuale;
	/*ACQUISIZIONE E CONTROLLO SCELTA*/
	
	while(scelta>=0){
		prezzo=leggi_prezzo();
	    percentuale= leggi_percentuale();
		if(scelta==0){
			calcola_prezzo_scontato(prezzo, percentuale);
		} 
		else if(scelta==1){
			calcola_prezzo_ivato(prezzo, percentuale);
		}

		scelta=leggi_scelta();
	}
}
/*FUNZIONI PER IL CONTROLLO E ACQUISIZIONE DELL'INPUT*/
int leggi_scelta(void){
	int temp;
	while(scanf("%d", &temp)!=1 || temp>1){
		printf("scelta non valida\n");
		scanf("%*[^\n]");
		scanf("%*c");
	}
	return temp;
}

float leggi_prezzo(void){
	float temp;
	while(scanf("%f", &temp)!=1 || temp<0){
		printf("Prezzo non valido\n");
		scanf("%*[^\n]");
		scanf("%*c");
	}
	return temp;
}

int leggi_percentuale(void){
	int temp;
	while(scanf("%d", &temp)!=1 || temp<0 || temp>100){
		printf("Percentuale non valida\n");
		scanf("%*[^\n]");
		scanf("%*c");
	}
	return temp;
}

/*FUNZIONI PER IL CALCOLO E STAMPA DELL'OUTPUT*/
void calcola_prezzo_scontato(float prezzo, int percentuale){
	printf("%20s\t%20s\t%20s\n","Prezzo_Init","Percentuale","Prezzo_scontato");
	printf("%20.2f\t%20.2f\t%20.2f\n",prezzo,(float)percentuale,prezzo*(100-percentuale)/100);
}

void calcola_prezzo_ivato(float prezzo, int percentuale){
	printf("%20s\t%20s\t%20s\n","Prezzo_Init","Percentuale","Prezzo_ivato");
	printf("%20.2f\t%20.2f\t%20.2f\n",prezzo,(float)percentuale,prezzo*(100+percentuale)/100);
}
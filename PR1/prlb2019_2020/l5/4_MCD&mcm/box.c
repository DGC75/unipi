#include <stdio.h>

int mcd(int a, int b);
int mcm(int a, int b);


/*START MAIN*/
int main(void){

	int n,m;
	/*ACQUISIZIONE E CONTROLLO DELL INPUT*/
	while(scanf("%d", &n)!=1 || n<=0){
		printf("Inserisci un intero positivo.\n");
		scanf("%*[^\n]");
		scanf("%*c");
	}
	while(scanf("%d", &m)!=1 || m<=0){
		printf("Inserisci un intero positivo.\n");
		scanf("%*[^\n]");
		scanf("%*c");
	}

	/*STAMPA OUTPUT*/
	printf("%d\n",mcd(n, m));
	printf("%d\n",mcm(n, m));
/*END MAIN*/
}

int mcd(int a, int b){
	/*IMPLEMENTAZIONE ALGORITMO DI EUCLIDE RICORSIVA (IN CODA?)*/
	if(a==1 || b==1){
		return 1;
	} else if(a>b){
		return mcd(b,a-b);
	} else if (b>a){
		return mcd(a,b-a);
	} else {
		return a;
	}
}
int mcm(int a, int b){
	/*MATH FACT: A*B=MCD(A,B)*MCM(A,B) */
	return a*b/mcd(a,b);
}
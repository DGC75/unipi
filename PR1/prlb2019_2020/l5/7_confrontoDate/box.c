#include <stdio.h>
#include <stdbool.h>

_Bool data_valida(int g, int m, int a);

int main(void){
	
	int g1=-1, m1=-1, a1=-1; 
	int g2=-1, m2=-1, a2=-1; 
	/*ACQUISIZIONE DATA1*/
	do{
		scanf("%d/%d/%d", &g1, &m1, &a1);
		scanf("%*[^\n]");
		scanf("%*c");
	}while(data_valida(g1, m1, a1)==false);


	while((g1!=0 || m1!=0 || a1!=0) && (g2!=0 || m2!=0 || a2!=0)){
			/*ACQUISIZIONE DATA2*/
		do{
		scanf("%d/%d/%d", &g2, &m2, &a2);
		scanf("%*[^\n]");
		scanf("%*c");
	}while(data_valida(g2, m2, a2)==false);

		/*SE LA DATA2 È PIÙ PICCOLA DELLA DATA1 (E DATA2 È DIVERSA DALL'USCITA) ALLORA DATA2 DIVENTA LA NUOVA DATA1*/
		if( ((a2<a1) || (a2==a1 && m2<m1) || (a2==a1 && m2==m1 && g2<g1)) && ( a2!=0 || m2!=0 || g2!=0)){
			g1=g2;
			m1=m2;
			a1=a2;
		} 
	}
	if(g2==0 && m2==0 && a2==0){
		printf("Data meno recente: %.2d/%.2d/%.4d\n",g1, m1, a1);
	}
}


_Bool data_valida(int g, int m, int a){
		/*CONTROLLO DELL'INPUT*/
		if( (a<0 || a>9999) || (m<0 || m>12) || (g<0 || g>31)){
			printf("Data inserita errata, inserire una data nel formato gg/mm/aaaa.\n");
			return false;
		}
		return true;
}

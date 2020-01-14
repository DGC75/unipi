#include <stdio.h>
#include <math.h>

int main(void){

	float a=0, b=0;
	char  operator=0;

	/*ACQUISIZIONE INPUT*/
    scanf("%f", &a);
    scanf("%f", &b);
    scanf("\n%c", &operator);


    /*CONTROLLO VALIDITÀ OPERATORE E STAMPA OUTPUT*/
    switch(operator){
    	case '+':
    	   printf("%.1f\n", a+b);
    	   break;
    	case '-':
    	   printf("%.1f\n", a-b);
    	   break;
    	case '/':
    	   printf("%.1f\n", a/b);
    	   break;
    	case '%':
    	   printf("%.1f\n", (float) ((int)floor(a) % (int)floor(b)) );
    	   break;
    	 default:
    	 printf("invalid operator\n");
    }

}
#include <stdio.h>

int main(){

    /*LEGGI n*/
    /*Leggi n prezzi e salvali in un arr*/

    int n = get_int();

    int *prices = alloc_arr(n);

    int i;
    for(i = 0; i < n; i++)
        prices[i] = get_int();
    
    /*STAMPA GUADAGNO MASSIMO*/
    /*STAMPA SUDDIVISIONE CHE GENERA IL GUADAGNO MAX.*/
    
    query(prices, n);

    return 0;
}

void query(int* prices, int dim){

    /*MATRICE PESI/NUMERI OGGETTI*/
    
}
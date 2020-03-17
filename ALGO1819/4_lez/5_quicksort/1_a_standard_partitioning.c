
#include <stdlib.h>
#include <stdio.h>
#include <time.h>

/* 
  !!!!!!!!!!!! D A  F A R E !!!!!!!!!!!!
  sx e dx sono le posizioni del primo e dell'ultimo elemento dell'array mentre 
  px è la posizione dell'elemento perno.
  La funzione deve restituire la posizione del perno dopo che gli elementi sono 
  stati partizionati.
*/
int distribuzione(int a[], int sx, int px, int dx) { 
  
  /*SWAP A[px] with A[dx]*/
  int k = a[px];
  a[px] = a[dx];
  a[dx] = k;
  /*IL RESTO DELLA PARTITION E' QUELLA STANDARD (LOMUTO) */
  int i = sx - 1;
  int j;
  for(j = sx; j < dx; j++){
    if(a[j] <= k){
        i++;
        /*SWAP A[i] WITH A[j]*/
        int tmp = a[i];
        a[i] = a[j];
        a[j] = tmp;
    }

  }
  /*SWAP A[i+1] WITH A[r] (PIVOT)*/
  int tmp = a[i + 1];
  a[i + 1] = a[dx];
  a[dx] = tmp;

  return i + 1; 
}

void quicksort( int a[], int sx, int dx ) {
  
  int perno, pivot;
  if( sx < dx ) {

    pivot = sx + rand()%(dx - sx + 1);
    perno = distribuzione(a, sx, pivot, dx); 
    /* Ordina ricorsivamente le due metà */
    quicksort(a, sx, perno - 1);
    quicksort(a, perno + 1, dx);
    
  }

}

/* Lettura di un array di interi da input. 
Il primo elemento è la lunghezza dell'array */
int legge(int **a, int *len) {

  int i;
  scanf("%d", len);
  if(*len <= 0) return 1;

  *a = (int *) malloc(*len * sizeof(int));
  if(*a == NULL) return 1;

  for( i = 0; i < *len; i++ ) 
	  scanf("%d", (*a)+i);
  
  return 0;

}

int main() {
  
  int i, n, *A;

  if( legge(&A, &n)) return 1;

  /*srand(time(NULL));*/
  quicksort(A, 0, n-1);
  
  /* Stampa l'array ordinato */
  for( i = 0; i < n; i++ ) 
    printf("%d ", A[i]);
	
  return 0;
}
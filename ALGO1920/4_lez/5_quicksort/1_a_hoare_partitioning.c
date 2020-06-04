
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

  int k = a[px];

  int j = dx + 1;
  int i = sx - 1;
/*
  printf("SOTTOARRAY DA %d a %d PRIMA DI PARTITION\n", sx, dx);
  printf("pivot a[%d] = %d\n", px, a[px]);
  int l;
  for(l =sx; l <= dx; l++){
    printf("%d ", a[l]);
  }
  puts("");
*/

  while(1 == 1){

    
    do{ j--; } while (a[j] > k);     
    do{ i++; } while (a[i] < k);
       
    
    if(i < j){
      /*SWAP*/
      int tmp = a[i];
      a[i] = a[j];
      a[j] = tmp;

    }
    else{
/*
    printf("SOTTOARRAY DA %d a %d DOPO PARTITION\n", sx, dx);
    printf("pivot a[%d] = %d\n", j, a[j]);
    for(l =sx; l <= dx; l++){
      printf("%d ", a[l]);
    }
    puts("");
    puts("");
    puts("");
*/

    return j;
    }

  }

}

void quicksort( int a[], int sx, int dx ) {
  
  int perno, pivot;
  if( sx < dx ) {

    pivot = sx + rand()%(dx - sx + 1);
    perno = distribuzione(a, sx, pivot, dx); 
    /* Ordina ricorsivamente le due metà */
    quicksort(a, sx, perno);
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

  srand(time(NULL));
  quicksort(A, 0, n-1);
  
  /* Stampa l'array ordinato */
  for( i = 0; i < n; i++ ) 
    printf("%d ", A[i]);
	
  return 0;
}
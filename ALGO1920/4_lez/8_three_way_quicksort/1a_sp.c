
#include <stdlib.h>
#include <stdio.h>
#include <time.h>

void swap(int *a, int *b){
  int tmp = *a;
  *a = *b;
  *b = tmp;
}

int distribuzione(int A[], int sx, int px, int *dim_px, int dx) { 

  int x = A[px];
  /*printf("pivot all'inizio di partition: A[%d] : %d\n", px, A[px]);*/
  int i = sx - 1;
  int j = sx - 1;


  swap(&A[px], &A[dx]);

  int h;
  for(h = sx; h < dx; h++){
    if(A[h] < x){
      i++;
      swap(&A[h], &A[i]);

      if(++j - i > 0){
        
        swap(&A[h], &A[j]);
      }
    } 
    else if( A[h] == x){
      j++;
      (*dim_px) += 1;
      swap(&A[h], &A[j]);
    }

  }

  swap(&A[dx], &A[++j]);
  
  return i + 1;
}

void quicksort( int a[], int sx, int dx ){
  
  int perno, pivot, equal_elements;
  if( sx < dx ) {

    equal_elements = 1;
    pivot = sx + rand()%(dx - sx + 1);
    perno = distribuzione(a, sx, pivot, &equal_elements, dx);
    /*printf("perno: %d, equal_elements: %d, sum : %d, dx: %d\n", perno, equal_elements, perno + equal_elements, dx);*/ 
    /* Ordina ricorsivamente le due metà */
    /* Mettiamo che il perno rappresenta l'indice della prima posizione
    del sotto-array di pivot e k la dimensione di questo array */
    quicksort(a, sx, perno - 1);
    quicksort(a, perno + equal_elements, dx);
    
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
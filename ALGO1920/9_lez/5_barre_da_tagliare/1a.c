#include <stdio.h>
#include <stdlib.h>


int get_int();
void mem_err();

int* alloc_arr(int);
int** alloc_2d_int_matr(int rows, int cols);

void query(int*, int);


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
    /*PESI = W = dim (lunghezza della barra da tagliare)*/
    /*NUMERO OGGETTI = S = dim*/

    int** matr = alloc_2d_int_matr(dim + 1, dim + 1);
    
    /*
    i = SET OF OBJECTS {1, 2, ..., i}
    j = PROGRESSIVE WEIGHT {1, 2, ..., j}
    */
    int i, j, m;
    for(i = 1; i < dim + 1; i++){
        for(j = 1; j < dim + 1; j++){
            matr[i][j] = matr[i - 1][j];
            /*POICHE' W[i] = i*/
            if( j >= i){
                m = matr[i - 1][j - i] + prices[i - 1];
                if(m > matr[i][j])
                    matr[i][j] = m;
            }
        }
    }

    printf("%d\n", matr[dim][dim]);
    /*TODO: PRINT ONE OF THE CORRECT SEQUENCES*/
}


int** alloc_2d_int_matr(int rows, int cols){

    int** tmp = calloc(rows, sizeof(int*));

    if(tmp == NULL)
        mem_err();

    int i;
    for(i = 0; i < rows; i++)
        tmp[i] = alloc_arr(cols);

    return tmp;
}

int* alloc_arr(int dim){
    
    int* tmp = calloc(dim, sizeof(int));

    if(tmp == NULL)
        mem_err();

    return tmp;
}

int get_int(){
    int tmp;
    scanf("%d", &tmp);
    scanf("%*[^\n]");
    scanf("%*c");

    return tmp;
}

void mem_err(){
    puts("memoria heap esaurita");
    exit(EXIT_FAILURE);
}
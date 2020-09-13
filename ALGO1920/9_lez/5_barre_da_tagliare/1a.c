#include <stdio.h>
#include <stdlib.h>


int get_int();
void mem_err();

int* alloc_arr(int dim);
void dealloc_arr(int* arr, int dim);
void print_arr_val(int *max_pieces, int dim);

int query(int* values,int* n_pieces, int dim);


int main(){

    /*LEGGI n*/
    /*Leggi n prezzi e salvali in un arr*/

    int n = get_int();

    int *values = alloc_arr(n);

    int i;
    for(i = 0; i < n; i++)
        values[i] = get_int();

   int max_val = 0;


    /*CALCOLA GUADAGNO MASSIMO*/
    max_val = query(values, n, 1);

    printf("%d\n", max_val);
    dealloc_arr(values, n);

    return 0;
}

int query(int* values, int dim, int pos){
    
    int max_val = 0;


}

void print_arr_val(int *max_pieces, int dim){
    
    int i;
    for(i = 0; i < dim; i++){
        while(max_pieces[i] > 0){
            printf("%d ", max_pieces[i]);
            max_pieces[i]-= 1;
        }
    }

    puts("");
}

void dealloc_arr(int* arr, int dim){

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
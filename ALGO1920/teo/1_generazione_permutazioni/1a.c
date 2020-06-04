#include <stdio.h>
#include <stdlib.h>

int     get_int(); 
int*    alloc_arr(int dim);

void    mem_err();

int main(){

    int dim = get_int();

    int *arr = alloc_arr(dim);
    genera_permutazioni(arr, 0, dim);

    return 0;
}

int get_int(){
    
    int tmp;
    scanf("%d", &tmp);
    scanf("%*c");

    return tmp;
}

int* alloc_arr(int dim){
    int* tmp = calloc(dim, sizeof(int));
    
    if(tmp == NULL)
        mem_err();

    return tmp;
}

void mem_err(){
    puts("Memoria heap esaurita.");
    exit(EXIT_FAILURE);
}
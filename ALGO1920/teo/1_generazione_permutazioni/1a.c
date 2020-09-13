#include <stdio.h>
#include <stdlib.h>

int     get_int(); 
int*    alloc_arr(int dim);
void    mem_err();

void gen_permut(int *arr, int dim, int pos);
void print_arr(int *arr, int dim);

int main(){

    int dim = get_int();

    int *arr = alloc_arr(dim);

    gen_permut(arr, dim, 0);

    return 0;
}

void gen_permut(int *arr, int dim, int pos){
    
    if (pos >= dim)
        return;

    int i;
    for(i = 1; i <= dim; i++){

        arr[pos] = i;
        
        if(pos == dim -1)
            print_arr(arr, dim);        
        
        gen_permut(arr, dim, pos + 1);
    }


       
}

void print_arr(int *arr, int dim){
    
    if(dim <= 0)
        return;
    
    int i;
    for(i = 0; i < dim; i++)
        printf("%d ", arr[i]);

    puts("");
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

    int i;
    for(i = 0; i < dim; i++)
        tmp[i] = 1;
    
    return tmp;
}

void mem_err(){
    puts("Memoria heap esaurita.");
    exit(EXIT_FAILURE);
}
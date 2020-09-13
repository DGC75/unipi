#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_STR_LEN 100


void mem_err();
int get_int();

int* alloc_arr(int dim);

void print_arr(int *arr, int dim);

int main(){
    
    int n = get_int();
    int *arr = alloc_arr(n);

    return 0;
}



void print_arr(int *arr, int dim){
    
    int i;
    for(i = 0; i < dim; i++)
        printf("%d ", arr[i]);

    puts("");
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

int* alloc_arr(int dim){
    
    if(dim <= 0)
        exit(EXIT_FAILURE);

    int *tmp = calloc(dim, sizeof(int));

    if(tmp == NULL)
        mem_err();

    return tmp;
}
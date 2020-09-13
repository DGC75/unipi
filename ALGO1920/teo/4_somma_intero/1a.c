#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_STR_LEN 100


void mem_err();
int get_int();

int* alloc_arr(int dim);
void print_arr(int *arr, int dim);

int alg(int dim, int *values, int pos);

int main(){
    
    int n = get_int();
    int *values = alloc_arr(n);

    int i;
    for(i = 0; i < n; i++)
        values[i] = get_int();
    
    printf("max:%d\n", alg(n, values, 0));


    return 0;
}


int alg(int dim, int *values, int pos){
    

    int i, tmp, max = 0;

    for(i = 1; i <= dim - pos; i++){
        tmp = values[i - 1] + alg(dim, values, pos + i);
        if(tmp > max)
            max = tmp;
    }

    return max;
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
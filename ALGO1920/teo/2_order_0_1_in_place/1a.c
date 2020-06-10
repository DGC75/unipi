#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int get_int();
void mem_err();


void print_arr_int(int *arr, int dim){
    int i;
    for(i = 0; i < dim; i++)
        printf("%d ", arr[i]);
    puts("");
}

int* load_arr_int(int dim){
    
    int* tmp = calloc(dim, sizeof(int));

    if(tmp == NULL)
        mem_err();

    int i;
    for(i = 0; i < dim; i++)
        tmp[i] = get_int();   
    
    return tmp;
}

void swap(int *a, int *b){
    int tmp = *a;
    *a = *b;
    *b = tmp;
}

void order_arr(int* arr, int dim){

    int i = 0, j = dim - 1;

    while(i <= j){        
        if( (arr[i] == 1) && (arr[j] == 0) ){
            swap(&(arr[i]),&(arr[j]));
            ++i;
            --j;
        }

        if(arr[i] == 0)
            ++i;
        if(arr[j] == 1)
            --j;
    }
}
int main(){

    int N = get_int();
    int *arr = load_arr_int(N);

    order_arr(arr, N);

    print_arr_int(arr, N);

    free(arr);
    arr = NULL;
    return 0;
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
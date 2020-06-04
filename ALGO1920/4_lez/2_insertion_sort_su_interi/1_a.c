#include <stdio.h>
#include <stdlib.h>

int  get_int(FILE *fPtr);
int* get_arr(FILE *fPtr, size_t dim1); 
void mem_err();
void print_arr(int *arr, size_t dim);

void insertion_sort(int *arr, size_t dim);

int main(){
    
    size_t dim = get_int(stdin);
    int *arr;

    arr = get_arr(stdin, dim);

    insertion_sort(arr, dim);

    print_arr(arr, dim); 

}

void insertion_sort(int *arr, size_t dim){
    
    int i, j, key;
    for(i = 1; i < dim; i++){
        key = arr[i];
        j = i - 1;
        while( j >= 0 && arr[j] > key){
            arr[j + 1] = arr[j];
            j--;
        }
        arr[j + 1] = key;
    }
}

void print_arr(int *arr, size_t dim){
    
    int i;
    
    for(i = 0; i < dim; i++)
        printf("%d\n", arr[i]);
}

void mem_err(){
    puts("Memoria esaurita.");
    exit(EXIT_FAILURE);
}

int get_int(FILE *fPtr){
    
    int input;
    fscanf(fPtr, "%d", &input);
    return input;
}

int* get_arr(FILE *fPtr, size_t dim1){
  
    int* arr = calloc(dim1, sizeof(int));
    if(arr == NULL)
        mem_err();
    

    int i;
    for(i = 0; i < dim1; ++i)
        arr[i] = get_int(fPtr);

    return arr;
} 
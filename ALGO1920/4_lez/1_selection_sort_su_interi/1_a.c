#include <stdio.h>
#include <stdlib.h>

int  get_int(FILE *fPtr);
int* get_arr(FILE *fPtr, size_t dim1); 
void mem_err();
void print_arr(int *arr, size_t dim);

void selection_sort(int *arr, size_t dim);

int main(){
    
    size_t dim = get_int(stdin);
    int *arr;

    arr = get_arr(stdin, dim);

    selection_sort(arr, dim);

    print_arr(arr, dim); 

}

void selection_sort(int *arr, size_t dim){
    int i, j, min, tmp;
    for(i = 0; i < dim - 1; i++){
        
        min = i;

        for(j = i + 1; j < dim; j++){
            if(arr[j] < arr[min])
                min = j;
        }

        /*SWAP A[min] with A[i]*/
        tmp = arr[min];
        arr[min] = arr[i];
        arr[i] = tmp;
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
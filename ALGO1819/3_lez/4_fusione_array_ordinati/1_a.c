#include <stdio.h>
#include <stdlib.h>

int  get_int(FILE *fPtr);
int* get_arr(size_t dim1, FILE *fPtr); 
void mem_err();

void print_arr_union(int arr1[], int arr2[], size_t dim1, size_t dim2);

int main(){
    
    int dim1, dim2;
    int *arr1, *arr2;
    
    dim1 = get_int(stdin);
    arr1 = get_arr(dim1, stdin);

    dim2 = get_int(stdin);
    arr2 = get_arr(dim2, stdin);

    print_arr_union(arr1, arr2, dim1, dim2);

}

void print_arr_union(int arr1[], int arr2[], size_t dim1, size_t dim2){
    
    int i = 0, j = 0;

    while( i < dim1 || j < dim2){
        if(arr1[i] < arr2[j]) {
            if(i < dim1)    
                printf("%d\n", arr1[i]);

            i++;
        }
        else{
            if(j < dim2) 
                printf("%d\n", arr2[j]);
            
            j++;    
        }

    }
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

int* get_arr(size_t dim1, FILE *fPtr){
  
    int* arr = calloc(dim1, sizeof(int));
    if(arr == NULL)
        mem_err();
    

    int i;
    for(i = 0; i < dim1; ++i)
        arr[i] = get_int(fPtr);

    return arr;
} 
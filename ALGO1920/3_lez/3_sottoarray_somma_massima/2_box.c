#include <stdio.h>
#include <stdlib.h>


int  get_int(FILE *fPtr);
int* get_arr(size_t dim1, FILE *fPtr); 
void mem_err();

int sub_arr_max_sum(int arr[], size_t dim);

int main(){
    
    int dim1 = get_int(stdin);
    int* arr1 = get_arr(dim1, stdin);  

    printf("%d\n", sub_arr_max_sum(arr1, dim1)); 
}

int sub_arr_max_sum(int arr[], size_t dim){
    
    int result = 0, temp;
    int size, i, j;
    for(size = 1; size <= dim; size++){
        for(i = 0; i + size - 1 < dim; i++){
            temp = 0;
            for(j = i; j <= i + size; j++){
                temp += arr[j]; 
            }
            if(temp > result)
                result = temp;
        }
    }

    return result;               
}


void mem_err(){
    puts("Memoria esaurita.");
    exit(EXIT_FAILURE);
}

int  get_int(FILE *fPtr){
    
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

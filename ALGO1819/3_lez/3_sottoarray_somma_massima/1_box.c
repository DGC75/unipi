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
    
    int sp1 = 0, sp2 = 0, sn = 0;
    int i = 0;

    while(i < dim && arr[i] <= 0)
        i++;

    for(; i < dim; i++){
        if(arr[i] > 0 && sn == 0)
            sp1 += arr[i];

        if(arr[i] <= 0)
            sn += arr[i];

        if(arr[i] > 0 && sn != 0)
            sp2 += arr[i];        
    } 

    if(sp2 + sn > 0)
        return sp1 + sp2 + sn;
    else 
        return sp1 > sp2 ? sp1 : sp2;                
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

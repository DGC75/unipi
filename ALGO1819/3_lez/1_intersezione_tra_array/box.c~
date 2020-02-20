#include <stdio.h>
#include <stdlib.h>

int  get_int(FILE *fPtr);
int* get_arr(size_t dim1, FILE *fPtr); 
int  n_inters_arrs(int arr1[], int arr2[], size_t dim1, size_t dim2);

void mem_err();

int main(){

    int dim1 = get_int(stdin);
    int* arr1 = get_arr(dim1, stdin);  
    
    int dim2 = get_int(stdin);
    int* arr2 = get_arr(dim2, stdin);   
    
    printf("%d\n", n_inters_arrs(arr1, arr2, dim1, dim2));
    
return 0; 
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


int  n_inters_arrs(int arr1[], int arr2[], size_t dim1, size_t dim2){

    int n_inters = 0;
    int i, j;
    for(i = 0; i < dim1; ++i){
        for(j = 0; j < dim2; ++j){
            if(arr1[i] == arr2[j])
                n_inters++;
        }    
    }
    
    return n_inters;
}

void mem_err(){
    puts("memoria esaurita.");
    exit(EXIT_FAILURE);
}

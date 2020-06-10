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


void merge_int(int *a, int p, int q, int r){
    int i = p;
    int j = q+1; 
    int k = 0;

    int *tmp = calloc(r-p+1,sizeof(int));

    while(i <= q && j <= r){

        while(a[i] <= a[j] && i <= q){
            tmp[k++] = a[i++];
        }
        while(a[j] <= a[i] && j <= r)
            tmp[k++] = a[j++];
    }

    while(i <= q){
        tmp[k++] = a[i++];
    }
    while(j <= r){
        tmp[k++] = a[j++];
    }
    for(k = p; k <= r; k++){
        a[k] = tmp[k-p];
    }
}


void merge_sort_int(int* arr, int p, int r){
    if(p < r){
        int q = (p +r)/2;

        merge_sort_int(arr, p, q);
        merge_sort_int(arr, q+1, r);

        merge_int(arr, p, q, r);
    }
}

int main(){

    int N = get_int();
    int *arr = load_arr_int(N);

    merge_sort_int(arr, 0, N-1);

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
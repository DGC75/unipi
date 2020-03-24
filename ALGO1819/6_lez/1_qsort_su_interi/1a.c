#include <stdio.h>
#include <stdlib.h>


int     get_int         (FILE *fPtr);
int*    get_arr         (FILE *fPtr, int size);
void    print_arr       (int *arr, size_t size);

int     even_el_arr     (int *arr, size_t size);

int     cmp_even_odd    (const void *a, const void *b);
int     cmp_asc         (const void *a, const void *b);
int     cmp_dsc         (const void *a, const void *b);

void    mem_err         ();


int main(void){
    
    int size =    get_int(stdin);
    int *arr =    get_arr(stdin, size);

    qsort(arr,  size,  sizeof(int),  cmp_even_odd);
    

    int sx   =    even_el_arr(arr, size);

    qsort(arr,          sx,        sizeof(int),     cmp_asc);
    qsort(arr + sx,     size - sx, sizeof(int),     cmp_dsc);

    /*print_arr(arr, size);*/
    print_arr(arr, size);
    return 0;
}

int even_el_arr (int *arr, size_t size){
    
    int i;
    for(i = 0; i < size && arr[i]%2 == 0; i++){};

    return i;
}


int cmp_dsc(const void *a, const void *b){
    return (*(int*)b - *(int*)a);
}

int cmp_asc(const void *a, const void *b){
    return *(int*)a - (*(int*)b);
}

int cmp_even_odd(const void *a, const void *b){
    
    if( (( (*(int*)a) + (*(int*)b)%2)) == 0 )
        return 0;
    else if( (*(int*)b)%2 == 0)
        return 1;
    else
        return -1;
}

int get_int(FILE *fPtr){
    
    int tmp; 
    fscanf(fPtr,"%d", &tmp);

    return tmp;
}
int* get_arr(FILE *fPtr, int size){
    
    /*SECURE ALLOC OF NEW ARRAY*/
    int *tmp_Ptr = calloc(size, sizeof(int));
    if(tmp_Ptr == NULL)
        mem_err();
    
    /*INIT NEW ARRAY*/
    int i;
    for(i = 0; i < size; i++)
        tmp_Ptr[i] = get_int(fPtr);

    return tmp_Ptr;
}

void print_arr(int *arr, size_t size){
    int i;
    for(i = 0; i < size; i++)
        printf("%d\n", arr[i]);
}

void mem_err(){

    puts("memoria esaurita");
    exit(EXIT_FAILURE);
}
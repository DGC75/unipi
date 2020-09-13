#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_STR_LEN 100

typedef struct node{
    
    int val;
    node* next;

}Node;

void mem_err();
int get_int();

int* alloc_arr(int dim);
void print_arr(int *arr, int dim);

int query(int *values, int dim, int* max_arr, int *seq);

int main(){
    
    int n = get_int();
    int *values = alloc_arr(n);
    int *m      = alloc_arr(n);
    Node *s      = alloc_arr(n);

    int i;
    for(i = 0; i < n; i++)
        values[i] = get_int();
    
    /*
    CALCOLA VARI SOTTOMASSIMI
    m1 = v1
    m2 = max(v1 + m1, v2)
    m3 = max(v1 + m2, v2 + m1, v3)
    ...
    m(n) = max(v1 + m(n-1), v2 + m(n-2), ... , vn)
    */

   /*
   ESTRAI SEQUENZA MASSIMA
   s1 = 1
   s2 = 1, s1 oppure 2.
   s3 = 1, s2 o 2, s1 o 3.
   sn = ...
   */
   
    printf("%d\n", query(values, n, m, s));
    print_seq(s);

    return 0;
}

int query(int *values, int dim, int* max_arr, int *seq){
    if()
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
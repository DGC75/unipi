#include <stdio.h>
#include <stdlib.h>


typedef int* Queue;

int get_int();
void mem_err();

Queue alloc_q(int dim);
void print_queue(Queue q, int dim);
void access_q(Queue* q_ptr, int dim, int x);


int main(){

    /*LEGGI N*/
    int N = get_int();
    Queue q = alloc_q(N);

    int e = get_int();

    while(e != 0){

        if(e == 2)
            print_queue(q, N);
        else if(e == 1){
            int x = get_int();
            access_q(&q, N, x);
        }

        e = get_int();
    }
    

    free(q);
    return 0;
}

void access_q(Queue* q_ptr, int dim, int x){
    
    int i = 0;
    while(i < dim && ((*q_ptr)[i] != -1) && (*q_ptr)[i] != x)
        i++;
    
    if(i == dim){
        /*EL NON PRESENTE NELL'ARRAY*/
        /*E CODA PIENA*/
        int j;
        for(j = dim - 1; j > 0 ; j--)
            (*q_ptr)[j] = (*q_ptr)[j - 1];
        (*q_ptr)[0] = x; 
    }
    else if((*q_ptr)[i] == -1){
        /*EL NON PRESENTE NELL'ARRAY*/
        /*E CODA NON PIENA*/  
        int j;
        for(j = i; j > 0 ; j--)
            (*q_ptr)[j] = (*q_ptr)[j - 1];        
        (*q_ptr)[0] = x;
    }
    else if((*q_ptr)[i] == x){
        /*EL GIA' PRESENTE NELL'ARRAY*/
        /*METTERE IN TESTA*/
        (*q_ptr)[i] = -1;
        int j;
        for(j = i; j > 0; j--)
            (*q_ptr)[j]  = (*q_ptr)[j - 1];
        (*q_ptr)[0] = x;
    }
}

void print_queue(Queue q, int dim){
    int i;
    for(i = 0; i < dim && q[i] != -1; i++)
        printf("%d ", q[i]);
    puts("$");
}

Queue alloc_q(int dim){
    
    Queue q = calloc(dim, sizeof(int));
    
    if(q == NULL)
        mem_err();
    int i;
    for(i = 0; i < dim; i++)
        q[i] = -1;
    
    return q;
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
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_STR_LEN 100

void mem_err();
int get_int();

int* alloc_arr(int dim);
void print_arr(int *arr, int dim);

void find_s_opt(int *values, int dim, int* maxs, int **seq_arr);

int** alloc_arr_of_arr(int dim);

int main(){
    
    int n = get_int();
    int *values = alloc_arr(n + 1);
    int *m      = alloc_arr(n + 1);
    int **s      = alloc_arr_of_arr(n + 1);

    int i;
    for(i = 0; i < n; i++)
        values[i + 1] = get_int();
    
    /*
    CALCOLA VARI SOTTOMASSIMI
    m0 = 0
    m1 = v1 + m0
    m2 = max(v1 + m1, v2)
    m3 = max(v1 + m2, v2 + m1, v3)
    ...
    m(n) = max(v1 + m(n-1), v2 + m(n-2), ... , vn)
    */
   find_s_opt(values, n, m, s);
   printf("%d\n", m[n]);
   /*
   ESTRAI SEQUENZA MASSIMA
   s1 = 1
   s2 = 1, s1 oppure 2.
   s3 = 1, s2 o 2, s1 o 3.
   sn = ...
   */
  int j;
  for(j = 0; j <= n; j++)
    print_arr(s[j], n);

  

  return 0;
}

int**alloc_arr_of_arr(int dim){

    int** tmp = calloc(dim, sizeof(int*));
    if(tmp == NULL)
        mem_err();
    
    int i;
    for(i = 0; i < dim; i++){
        tmp[i] = calloc(dim - 1, sizeof(int));
        if(tmp[i] == NULL)
            mem_err();
    }
    
    return tmp;
}


void find_s_opt(int *values, int dim, int *maxs, int** seq_arr){
    

    int i,j, t_max;

    seq_arr[1][0] = 1; 
    for(i = 1; i <= dim + 1; i++){
        
        for(j = 1; j <= i; j++){
            /*
            j-1 := valore di V attualmente considerato (j)
            i-j := valore di maxs attualmente considerato (i-j)
            */
            t_max = values[j - 1] + maxs[i -j]; 
            
            if(t_max > maxs[i - 1]){
                printf("t_max=%d\n", t_max);
                int l = 0;
                /*
                s[i] = j concat s[i-j]
                */
                if(i <= dim){
                    seq_arr[i][l] = j;
                    printf("j:%d\n", j);
                }
                
                l+=1;

                while(i <= dim && l < dim){
                    seq_arr[i][l] = seq_arr[i-j][l-1];
                    l += 1;

                }
                
                maxs[i - 1] = t_max;
            }
        }

    }
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
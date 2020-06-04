#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

#define MAX_STRING_LENGTH 100

int get_int(FILE *fPtr);
char** get_strings(FILE *fPtr, int size);
void free_strings(char ***strings, int size);

int partition(char ***strings, int p, int pivot, int r);
void q_sort_strings(char ***strings, int p, int r);
void print_strings(char **strings, int size);

void mem_err();

int main(){
    srand(time(NULL));
    int size;

    size = get_int(stdin);

    char** strings = get_strings(stdin, size);
    
    q_sort_strings(&strings, 0, size - 1);
    print_strings(strings, size);
    
    free_strings(&strings, size);
}

void q_sort_strings(char ***strings, int p, int r){

    if(p < r){
        int perno, pivot;
        pivot = p + rand()%(r - p + 1);
        perno = partition(strings, p, pivot, r);

        q_sort_strings(strings, p, perno - 1);
        q_sort_strings(strings, perno + 1, r);
    }
}

int partition(char ***strings, int p, int pivot, int r){
    
    /*SWAP PIVOT-STRING AND LAST STRING*/
    char *tmp = *(*strings + r);
    *(*strings + r) = *(*strings + pivot);
    *(*strings +  pivot) = tmp;
    
    /*LOMUTO PARTITIONING*/
    /*x: PIVOT*/
    char *x = *(*strings + r);

    int i = p - 1;

    int j;
    for(j = p; j < r; j++){
        if(strcmp(*(*strings + j), x) <= 0){
            i = i + 1;
            /*SWAP strings[i] AND strings[j]*/
            tmp = *(*strings + i);
            *(*strings + i) = *(*strings + j);
            *(*strings + j) = tmp;
        }
    }
    /*PUT PIVOT IN THE RIGHT PLACE: LAST POSITION OF i-SUBARRAY*/
    /*SWAP strings[i + 1] AND strings[r]*/
    i = i + 1;
    tmp = *(*strings + i); 
    *(*strings + i) = *(*strings + r);
    *(*strings + r) = tmp;
    
    return i;
}

void print_strings(char **strings, int size){
    int i;
    for(i = 0; i < size; i++)
        printf("%s", strings[i]);
}

int get_int(FILE *fPtr){
    
    int input;
    fscanf(fPtr, "%d", &input);
    fscanf(fPtr, "%*c");
    return input;
}

char** get_strings(FILE *fPtr, int size){
    
    char **arr_of_strings = calloc(size, sizeof(char*));
    
    if(arr_of_strings == NULL)
        mem_err();
    int i;
    for(i = 0; i < size; i++){
        arr_of_strings[i] = calloc(MAX_STRING_LENGTH + 1, sizeof(char));
        if(arr_of_strings[i] == NULL)
            mem_err();
        
        fgets(arr_of_strings[i], MAX_STRING_LENGTH + 1, fPtr);
    }

    return arr_of_strings;
}




void free_strings(char ***strings, int size){
    /*HELO*/
}


void mem_err(){
    puts("Memoria esaurita.");
    exit(EXIT_FAILURE);
}
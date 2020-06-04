#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_STRING_LENGTH 100

int get_int(FILE *fPtr);
char** get_strings(FILE *fPtr, int size);
void string_insertion_sort(char ***stringsPtr, int size);
void print_strings(char** strings, int size);
void free_strings(char ***strings, int size);

void mem_err();

int main(){
    
    int size = get_int(stdin);

    char** strings = get_strings(stdin, size);

    string_insertion_sort(&strings, size);

    print_strings(strings, size);

    free_strings(&strings, size);
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
        arr_of_strings[i] = calloc(MAX_STRING_LENGTH, sizeof(char));
        if(arr_of_strings[i] == NULL)
            mem_err();
        fgets(arr_of_strings[i], MAX_STRING_LENGTH, stdin);
    }

    return arr_of_strings;
}

void string_insertion_sort(char ***stringsPtr, int size){
    
    int i, j;
    char key[MAX_STRING_LENGTH] = {'\0'};

    for(i = 1; i < size; i++){
        strcpy(key, *(*stringsPtr + i) );
        
        j = i - 1;
        while(j >= 0 && (strcmp(*(*stringsPtr + j), key) > 0)){
            strcpy(*(*stringsPtr + j+1) , *(*stringsPtr + j));
            j--;
        }

        strcpy(*(*stringsPtr + j + 1), key);
    }
}

void print_strings(char** strings, int size){
    int i;
    for(i = 0; i < size; i++)
        printf("%s", strings[i]);
}

void free_strings(char ***strings, int size){
    
}


void mem_err(){
    puts("Memoria esaurita.");
    exit(EXIT_FAILURE);
}
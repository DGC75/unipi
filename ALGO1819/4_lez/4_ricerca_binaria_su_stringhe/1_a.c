#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_STRING_LENGTH 100

int get_int(FILE *fPtr);
char** get_strings(FILE *fPtr, int size);
int string_binary_search(char **arr_of_strings, char *string, int start, int end);
void free_strings(char ***strings, int size);

void mem_err();

int main(){
    
    int size, menu_item;
    char string[MAX_STRING_LENGTH] = {'\0'};

    size = get_int(stdin);

    char** strings = get_strings(stdin, size);


    menu_item = get_int(stdin);

    while(menu_item != 0){

        fgets(string, MAX_STRING_LENGTH, stdin);
        printf("%d\n", string_binary_search(strings, string, 0, size));
        menu_item = get_int(stdin);
    }


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

int string_binary_search(char **arr_of_strings, char *string, int start, int end){
    
    
    if(start == end)
        return -1;
    else{
        int q = (start + end)/2; 
        int cmp = strcmp(string,arr_of_strings[q]);
        if(cmp > 0)
            return string_binary_search(arr_of_strings,string, q+1,  end);
        
        else if(cmp < 0)
            return string_binary_search(arr_of_strings,string, start,  q);
        else
            return q;
    }    
}


void free_strings(char ***strings, int size){
    /*HELO*/
}


void mem_err(){
    puts("Memoria esaurita.");
    exit(EXIT_FAILURE);
}
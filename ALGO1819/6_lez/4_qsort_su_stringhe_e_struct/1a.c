#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define IN_STREAM       stdin
#define MAX_STRING_SIZE 100

typedef struct{

    char string[MAX_STRING_SIZE + 1];
    int length;

}String;

int     string_cmp          (const void *a, const void *b);
int     get_int             (FILE *fPtr);
String* get_string_arr      (FILE *fPtr, int size);
void    print_string_arr    (String *arr, int size);
int     get_str_len         (FILE *fPtr);

void    free_string_arr     (String **arr, int size);
void    mem_err             ();
void    err                 ();


int main(){

    int size = get_int(IN_STREAM);
    String *string_arr = get_string_arr(IN_STREAM, size);

    qsort(string_arr, size, sizeof(String), string_cmp);
    print_string_arr(string_arr, size);

    free_string_arr(&string_arr, size);

    return 0;
}

int string_cmp (const void *a, const void *b){
    
    String* str1 = (String *) a;
    String* str2 = (String *) b;

    if(str1->length > str2->length)
        return 1;
    else if(str1->length < str2->length)
        return -1;
    else{
        return strcmp(str1->string, str2->string);
    }
}

int get_int (FILE *fPtr){
    
    int tmp;
    fscanf(fPtr,"%d", &tmp);
    
    /*CLEAN BUFFER*/
    fscanf(fPtr,"%*[^\n]");
    fscanf(fPtr,"%*c");

    return tmp;
}

String* get_string_arr (FILE *fPtr, int size){
    
    String* tmp_string_arr = calloc(size, sizeof(String));

    if(tmp_string_arr == NULL)
        mem_err();
    
    int str_len;
    int i;
    for(i = 0; i < size; i++){
        
        str_len = get_str_len(fPtr);
        if(fgets(tmp_string_arr[i].string, MAX_STRING_SIZE + 1, fPtr) == NULL)
            err();
        
        tmp_string_arr[i].string[str_len] = '\0';
        tmp_string_arr[i].length = str_len;
    }

    return tmp_string_arr;
}

void print_string_arr (String *arr, int size){
    int i;
    for(i = 0; i < size; i++)
        printf("%s\n", arr[i].string);
}

void mem_err(){
    puts("Memoria esaurita.");
    exit(EXIT_FAILURE);
}

void err(){
    puts("Qualcosa e' andato storto.");
    exit(EXIT_FAILURE);
}

int get_str_len (FILE *fPtr){
    
    fpos_t start;
    fgetpos(fPtr, &start);

    int result = 0;

    while(fgetc(fPtr) != '\n')
        result++;
    
    fsetpos(fPtr, &start);
    return result;
}

void free_string_arr(String **arr, int size){

    free(*arr);
    *arr = NULL;
}
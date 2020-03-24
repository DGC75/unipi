#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_STR_SIZE 90

int     get_int         (FILE *fPtr);
char   *get_string      (FILE *fPtr);
char  **get_str_arr     (FILE *fPtr, int size);  
int     strcmp_dsc      (const void *s1, const void *s2);
int     get_str_len     (FILE *fPtr);

void    print_arr_str   (char **str_arr, int size);

int main(void){
    
    int size = get_int(stdin);
    char **str_arr = get_str_arr(stdin, size);

    qsort(str_arr, size, sizeof(char*), strcmp_dsc);
    print_arr_str(str_arr, size);    
}

char **get_str_arr (FILE *fPtr, int size){
    
    char **tmp_arr = calloc(size, sizeof(char*));
    
    int i;
    for(i = 0; i < size; i++)
        tmp_arr[i] = get_string(fPtr);
    
    return tmp_arr;
}


int strcmp_dsc(const void *s1, const void *s2){

    char **t1 = (char **) s1;
    char **t2 = (char **) s2; 
	return -1*strcmp(*t1, *t2);
}

void print_arr_str (char **str_arr, int size){
    int i;
    for(i = 0; i < size; i++)
        printf("%s\n", str_arr[i]);
}

char *get_string (FILE *fPtr){

    char* tmp_string = calloc(MAX_STR_SIZE + 1, sizeof(char));
    
    
    int str_len = get_str_len(fPtr);

    fgets(tmp_string, str_len + 1, fPtr);

    fscanf(fPtr,"%*c");
    return tmp_string;
}

int get_str_len(FILE *fPtr){
    
    int result = 0;

    fpos_t start; 
    fgetpos(fPtr,&start);
    while(fgetc(fPtr) != '\n')
        result++;
        

    fsetpos(fPtr, &start);
    return result;
}


int get_int(FILE *fPtr){

    int tmp;
    fscanf(fPtr,"%d", &tmp);
    fscanf(fPtr,"%*c");

    return tmp;
}

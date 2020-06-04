#include <stdio.h>
#include <string.h>
#include <stdlib.h>

#define MAX_STR_LEN 100

typedef struct{
    
    char *str;
    int occ;

}Stringa;

int         str_cmp                 (const void *a, const void *b);
int         struct_str_cmp          (const void *a, const void *b);
int         struct_int_cmp          (const void *a, const void *b);

int         count_different_strings (char** str_arr,int dim);

char**      get_arr_of_strings      (int dim);
Stringa**   get_arr_of_str_struct   (char ** str_arr, int dim, int* new_size);

void        mem_err                 ();
void        err                     ();

void        free_arr_of_strings     (char ***arr, int dim);
void        free_arr_of_structs     (Stringa ***arr, int dim);

int main(){

    /*LEGGI N*/
    int n;
    scanf("%d", &n);

    /*PULIZIA BUFFER*/
    scanf("%*[^\n]");
    scanf("%*c");

    /*LEGGI K*/
    int k;
    scanf("%d", &k);

    /*PULIZIA BUFFER*/
    scanf("%*[^\n]");
    scanf("%*c");

    /*SALVA TUTTE LE STRINGHE IN A, ARRAY DI STRINGHE*/

    char ** arr_of_strings = get_arr_of_strings(n);

    /*ORDINA A PER ORDINE LESSICOGRAFICO*/

    qsort(arr_of_strings, n, sizeof(char*), str_cmp);
    
    /*ALLOCA NUOVO ARRAY DI STRUCT B{STRINGA, OCCORRENZE}*/

    int size_new_arr;

    Stringa ** new_arr_of_strings = get_arr_of_str_struct(arr_of_strings, n, &size_new_arr);

    /*ORDINA TUTTO IL NUOVO ARRAY PER NUMERO DI OCCORRENZE*/
    
    qsort(new_arr_of_strings, size_new_arr, sizeof(Stringa*), struct_int_cmp);        

    /*ORDINA LE PRIME k IN ORDINE LESSICOGRAFICO E STAMPA*/

    qsort(new_arr_of_strings, k, sizeof(Stringa*), struct_str_cmp); 
    
    int i;

    for(i = 0; i < k; i++)
        printf("%s\n", new_arr_of_strings[i]->str);
    
    /*DEALLOCA MEMORIA*/

    free_arr_of_strings(&arr_of_strings, n);
    free_arr_of_structs(&new_arr_of_strings, size_new_arr);

}

int str_cmp (const void *a, const void *b){

    char* a_str = *(char**) a;
    char* b_str = *(char**) b;


    return strcmp(a_str, b_str);
}

int struct_str_cmp (const void *a, const void *b){
    
    Stringa* a_struct = *(Stringa**) a;
    Stringa* b_struct = *(Stringa**) b;

    return strcmp(a_struct->str, b_struct->str);
}

int struct_int_cmp (const void *a, const void *b){
    
    Stringa* a_struct = *(Stringa**) a;
    Stringa* b_struct = *(Stringa**) b;

    if(a_struct->occ > b_struct->occ){
        return -1;
    }
    else if(a_struct->occ < b_struct->occ){
        return 1;
    }
    else{
        return 0;
    }
}

char** get_arr_of_strings (int dim){
    
    char **new_arr_of_strings = calloc(dim ,sizeof(char*));

    if(new_arr_of_strings == NULL)
        mem_err();
    
    int i;    
    for(i = 0; i < dim; i++){
        
        new_arr_of_strings[i] = calloc(MAX_STR_LEN + 1, sizeof(char));
        
        if(new_arr_of_strings[i] == NULL)
            mem_err();

        if(fgets(new_arr_of_strings[i], MAX_STR_LEN + 1, stdin) == NULL)
            err();
        
        new_arr_of_strings[i][strlen(new_arr_of_strings[i]) - 1] = '\0';
    }



    return new_arr_of_strings;
}

Stringa** get_arr_of_str_struct (char ** str_arr, int dim, int* new_size){
    
    int size = count_different_strings(str_arr, dim);

    Stringa** new_arr_of_structs = calloc(size, sizeof(Stringa*));

    if(new_arr_of_structs == NULL)
        mem_err();



    new_arr_of_structs[0] = calloc(1, sizeof(Stringa));
    
    if(new_arr_of_structs[0] == NULL)
        mem_err();

    new_arr_of_structs[0]->occ = 1;
    new_arr_of_structs[0]->str = str_arr[0];

    int i = 1;
    int j = 0; /*INDICE ARRAY DI STRUCTS*/

    while(i < dim){
        
        if(strcmp(str_arr[i - 1], str_arr[i]) != 0){
            j++;
            /*ALLOCA NUOVA STRUCT E INIZIALIZZA*/
            
            new_arr_of_structs[j] = calloc(1, sizeof(Stringa));

            if(new_arr_of_structs[j] == NULL)
                mem_err();
            
            new_arr_of_structs[j]->occ = 1;
            new_arr_of_structs[j]->str = str_arr[i];
        }
        else{
            new_arr_of_structs[j]->occ += 1;
            
        }
        i++;
    }
    *new_size = size;
    return new_arr_of_structs;
}

void mem_err(){
    puts("memoria esaurita.");
    exit(EXIT_FAILURE);
}

void err(){
    puts("errore generico.");
    exit(EXIT_FAILURE);
}

int count_different_strings(char** str_arr,int dim){
    
    int result = 1;

    int i;
    for(i = 0; i < dim - 1; i++)
        if(strcmp(str_arr[i], str_arr[i + 1]) != 0)
            result++;

    return result;
}

void free_arr_of_strings(char ***arr, int dim){
    int i;
    for(i = 0; i < dim; i++){
        free( *(*arr + i));
        *(*arr + i) = NULL;
    }
    free(*arr);
    *arr = NULL;
}

void free_arr_of_structs(Stringa ***arr, int dim){

    int i;
    for(i = 0; i < dim; i++){
        free( *(*arr + i));
        *(*arr + i) = NULL;
    }
    free(*arr);
    *arr = NULL;

}
#include <stdio.h>
#include <string.h>
#include <stdlib.h>

#define MAX_STR_LEN 100

typedef struct{
    
    char str[MAX_STR_LEN + 1];
    int occ;

}Stringa;

int         str_cmp                 (const void *a, const void *b);
int         struct_str_cmp          (const void *a, const void *b);
int         struct_int_cmp          (const void *a, const void *b);

char**      get_arr_of_strings      (int dim);
Stringa*    get_arr_of_str_struct   (char ** str_arr, int dim);

void        partial_heapsort        (Stringa* arr_of_structs, int dim_tot, int k, int (*compar)(const void *, const void *));

void        mem_err                 ();
void        err                     ();

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

    /*SALVA TUTTE LE STRINGHE IN A ARRAY DI STRINGHE*/

    char ** arr_of_strings = get_arr_of_strings(n);

    /*ORDINA A PER ORDINE LESSICOGRAFICO*/

    qsort(arr_of_strings, n, sizeof(char*), str_cmp);
    
    /*ALLOCA NUOVO ARRAY DI STRUCT B{STRINGA, OCCORRENZE}*/

    Stringa* new_arr_of_strings = get_arr_of_str_struct(arr_of_strings, n);

    /*ORDINA PARZIALMENTE SOLO LE PRIME k PER NUMERO DI OCCORRENZE*/

    partial_heapsort(new_arr_of_strings, n, k, struct_int_cmp);

    /*ORDINA LE PRIME k IN ORDINE LESSICOGRAFICO E STAMPA*/

    partial_heapsort(new_arr_of_strings, n, k, struct_str_cmp);
    
    int i;
    for(i = 0; i < n; i++)
        printf("%s\n", arr_of_strings[i]);
    
    
    /*DEALLOCA MEMORIA*/
    /*free()*/
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

    if(a_struct->occ > b_struct->occ)
        return 1;
    else if(a_struct->occ < b_struct->occ)
        return -1;
    else
        return 0;
}

char** get_arr_of_strings (int dim){
    
    char ** new_arr_of_strings = calloc(dim ,sizeof(char*));

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
Stringa* get_arr_of_str_struct (char ** str_arr, int dim){
    
    int size = count_different_strings(*str_arr, dim);
    Stringa** new_arr_of_structs = calloc(size, sizeof(Stringa*));

    if(new_arr_of_structs == NULL)
        mem_err();
    

}

void partial_heapsort (Stringa* arr_of_structs, int dim_tot, int k, int (*compar)(const void *, const void *)){

}

void mem_err(){
    puts("memoria esaurita.");
    exit(EXIT_FAILURE);
}

void err(){
    puts("errore generico.");
    exit(EXIT_FAILURE);
}

int count_different_strings(char * str_arr,int dim){
    
    int result = 0;

    int i;
    for(i = 0; i < dim; i++){
        
    }

    return result;
}
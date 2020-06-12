#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_STR_LEN 100

char* get_str();
int get_int();
void mem_err();

typedef struct node{
    
    struct node* left;
    struct node* right;

    char* key;
    int val;

}Node;

typedef Node* Tree;


int max_val(Tree t);
int max(int a, int b);
void abr_insert(Tree* t_ptr, int val, char *key);
int decomp(Tree t, char* str);
void free_abr(Tree* t_ptr);

void print_t(Tree t){
    if(t != NULL){
        print_t(t->left);
        printf("%s %d\n", t->key, t->val);
        print_t(t->right);
    }
}

int main(){

    Tree abr = NULL;
    
    /*LEGGI N*/
    int N = get_int();
    
    /*INSERISCI N OGGETTI NELL'ALBERO*/
    int i;
    for(i = 0; i < N; i++)
        abr_insert(&abr, get_int(), get_str());
    

    /*LEGGI STRINGA str*/
    char str[MAX_STR_LEN + 1] = {'\0'};
    fgets(str, MAX_STR_LEN + 1, stdin);
    str[strlen(str) - 1] = '\0';

    /*RESTITUISCI IL VALORE MASSIMO DEL SOTTOALBERO*/
    /*RADICATO IN str*/
    printf("%d\n", decomp(abr, str));

    /*DEALLOCA ALBERO*/
    free_abr(&abr);

    return 0;
}

void abr_insert(Tree* t_ptr, int val, char* key){
    if(t_ptr != NULL){
        if(*t_ptr == NULL){
            Node *new_nd = calloc(1, sizeof(Node));
            
            if(new_nd == NULL)
                mem_err();
            
            new_nd->key = key;
            new_nd->val = val;

            *t_ptr = new_nd;
            return;
        }
        
        if(strcmp(key, (*t_ptr)->key) < 0)
            abr_insert(&((*t_ptr)->left), val, key);
        else
            abr_insert(&((*t_ptr)->right), val, key);

    }
}

int decomp(Tree t, char* str){

    if(t == NULL)
        return -1;
    
    if(strcmp(str, t->key) == 0)
        return max_val(t);
    else{
        int t_left = decomp(t->left, str);
        int t_right = decomp(t->right, str);

        return max(t_left, t_right);
    }



}

void free_abr(Tree* t_ptr){
    if(t_ptr != NULL && *t_ptr != NULL){
        free((*t_ptr)->key);
        free_abr(&((*t_ptr)->left));
        free_abr(&((*t_ptr)->right));

        free(*t_ptr);
        *t_ptr = NULL;
    }
}

int max_val(Tree t){
    /*CASI BASE*/
    if(t == NULL)
        return -1;
    else if(t->left == NULL && t->right == NULL)
        return t->val;
    
    int t_l = max_val(t->left);
    int t_r = max_val(t->right);

    return max(t_l, t_r);
}

int max(int a, int b){
    if(a - b > 0)
        return a;
    
    return b;
}

char* get_str(){

    char* new_str = calloc(MAX_STR_LEN + 1, sizeof(char));

    if(new_str == NULL)
        mem_err();

    fgets(new_str, MAX_STR_LEN + 1, stdin);

    new_str[strlen(new_str) - 1] = '\0';

    return new_str;
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

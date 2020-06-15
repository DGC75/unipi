#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_STR_LEN 101

typedef struct node{
    struct node* left;
    struct node* right;
    char *key;
} Node;

typedef Node* Tree;

void abr_insert(Tree* t_ptr, char *key);
void free_tree(Tree* t_ptr);
char* get_string();
int get_int();
void mem_err();
void prefix(Tree t);
int is_prefix(char *prefixer, char* prefixed);

char* m(Tree t);

void print_tree(Tree t){
    if(t != NULL){
        print_tree(t->left);
        printf("%s\n", t->key);
        print_tree(t->right);
    }
}

int main(){


    Tree t = NULL;
    int N = get_int();

    int i;
    for(i = 0; i < N; i++)
        abr_insert(&t, get_string());
    

    prefix(t);

    free_tree(&t);
    return 0;
}


void prefix(Tree t){
    if(t != NULL){
        prefix(t->left);
        
        if(is_prefix(m(t), t->key) == 1)
            printf("%s\n", t->key);
        
        prefix(t->right);
    }
}

int is_prefix(char *prefixer, char* prefixed){

    int result = strncmp(prefixer, prefixed, strlen(prefixer));

    if(result == 0)
        return 1;
    
    return 0;
}

char *m(Tree t){
    if(t != NULL){
        if(t->left != NULL)
            return m(t->left);
        
        return t->key;
    }

    return "YOU SHOULD NOT GET HERE";
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


void abr_insert(Tree* t_ptr, char* key){
    if(t_ptr != NULL){
        if(*t_ptr == NULL){
            Node *new_node = calloc(1, sizeof(Node));

            if(new_node == NULL)
                mem_err();

            new_node->key = key;
            *t_ptr = new_node;
            return;

        }

        if(strcmp(key, (*t_ptr)->key) < 0)
            abr_insert(&((*t_ptr)->left), key);
        else
            abr_insert(&((*t_ptr)->right), key);
    }
}

void free_tree(Tree* tree_ptr){
    if(tree_ptr != NULL && *tree_ptr != NULL){
        free_tree(&((*tree_ptr)->left));
        free_tree(&((*tree_ptr)->right));
        
        free( (*tree_ptr)->key);
        (*tree_ptr)->key = NULL;
        free(*tree_ptr);
        *tree_ptr = NULL;
    }
}

char* get_string(){
    
    char arr[MAX_STR_LEN + 1] = {'\0'};

    fgets(arr, MAX_STR_LEN + 1, stdin);

    arr[strlen(arr) - 1] = '\0';


    char *tmp = calloc(strlen(arr) + 1, sizeof(char));

    if(tmp == NULL)
        mem_err();

    strncpy(tmp, arr, strlen(arr));

    return tmp;
}
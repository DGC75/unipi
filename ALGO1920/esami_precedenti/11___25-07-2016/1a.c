#include <stdio.h>
#include <stdlib.h>
#include <string.h>


typedef struct node{
    struct node* left;
    struct node* right;
    int key;
} Node;

typedef Node* Tree;

int get_int();
void mem_err();
void abr_insert(Tree* t_ptr, int key);
void free_tree(Tree* t_ptr);
int mediana(Tree t, int dim);


int main(){

    Tree t = NULL;
    int N = get_int();
    
    int i;
    for(i = 0; i < N; i++)
        abr_insert(&t, get_int());

    printf("%d\n", mediana(t, N));

    free_tree(&t);

    return 0;
}

/*IMPLEMENTAZIONE CON VISITA SIMMETRICA ITERATIVA*/
/*USO DI STACK NECESSARIO*/

int mediana(Tree t, int dim){
    
    int rank = dim/2;
    int counter = 0;
    Node** stack = calloc(dim, sizeof(Node*));
    int dim_stack = 0;

    while(dim_stack != 0 || t != NULL){
        if(t != NULL){
            stack[dim_stack++] = t;
            t = t->left;
        }
        else{
            t = stack[--dim_stack];
            stack[dim_stack] = 0;
            counter +=1;
            
            if(counter == rank + 1){
                    free(stack);
                    return t->key;
            }
                
            t = t->right;
        }
    }
    
    return -1;
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

void abr_insert(Tree* t_ptr, int key){
    if(t_ptr != NULL){
        if(*t_ptr == NULL){
            Node *new_node = calloc(1, sizeof(Node));

            if(new_node == NULL)
                mem_err();

            new_node->key = key;
            *t_ptr = new_node;
            return;

        }

        if(key < (*t_ptr)->key)
            abr_insert(&((*t_ptr)->left), key);
        else
            abr_insert(&((*t_ptr)->right), key);
    }
}

void free_tree(Tree* tree_ptr){
    if(tree_ptr != NULL && *tree_ptr != NULL){
        free_tree(&((*tree_ptr)->left));
        free_tree(&((*tree_ptr)->right));
        free(*tree_ptr);
        *tree_ptr = NULL;
    }
}
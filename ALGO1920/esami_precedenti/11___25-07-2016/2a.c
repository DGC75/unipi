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


void io_visit(Tree t, int *count_ptr, int rank, int *output){
    if(t != NULL){
        io_visit(t->left, count_ptr, rank, output);
        *count_ptr += 1;
        if(*count_ptr == rank+1){
            *output = t->key;
            return;
        }
        io_visit(t->right, count_ptr, rank, output);
    }
}

/*IMPLEMENTAZIONE CON VISITA SIMMETRICA RICORSIVA*/
int mediana(Tree t, int dim){
    
    int rank = dim/2;
    int count = 0;
    int output;

    io_visit(t, &count, rank, &output);

    return output;
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
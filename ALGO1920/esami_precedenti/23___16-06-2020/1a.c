#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_STR_LEN 100

typedef struct _node{
    int key;
    struct  _node *left;
    struct  _node *right;
} Node;

typedef Node* Tree;

void mem_err();
int get_int();

void abr_insert(Tree* t_ptr, int val);
void free_tree(Tree* t_ptr);

int abr_query(Tree t, int *sbil_max);

int max(int a, int b){
    
    if(a - b >= 0)
        return a;
    
    return b;
}

int main(){

    Tree t = NULL;
    int N = get_int();

    int i;
    for(i = 0; i < N; i++)
        abr_insert(&t, get_int());


    int sbil_max = 0;
    abr_query(t, &sbil_max);

    printf("%d\n", sbil_max);

    free_tree(&t);
    return 0;
}

int abr_query(Tree t, int *sbil_max){
    
    if(t == NULL)
        return 0;

    if(t->left == NULL && t->right == NULL)
        return 1;
    
    int dim_left = abr_query(t->left, sbil_max);
    int dim_right = abr_query(t->right, sbil_max);

    int tmp = abs(dim_left - dim_right);

    if(tmp > *sbil_max)
        *sbil_max = tmp;

    return 1 + dim_left + dim_right;    
}

void abr_insert(Tree* t_ptr, int val){
    
    if(t_ptr != NULL){
    
        if(*t_ptr == NULL){
        
            Node *new_node = calloc(1, sizeof(Node));

            if(new_node == NULL)
                mem_err();

            new_node->key = val;
            *t_ptr = new_node;
            return;

        }

        if( (val < (*t_ptr)->key) || (val == (*t_ptr)->key) )
            abr_insert(&((*t_ptr)->left), val);
        else
            abr_insert(&((*t_ptr)->right), val);
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


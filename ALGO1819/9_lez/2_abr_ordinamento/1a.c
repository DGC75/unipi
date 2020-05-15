#include <stdio.h>
#include <stdlib.h>


typedef struct node{
    int val;
    struct node* left;
    struct node* right;
} Node;

typedef Node* Tree;
 
Node*   alloc_new_node();
void    mem_err();
int     get_int();
void    abr_insert(Tree* tree_ptr, int val);
void    abr_query(Tree tree);
void    free_tree(Tree* tree_ptr);
int     max(int c1, int c2);

int main(){

    Tree tree = NULL;

    /*LEGGI N*/
    int N = get_int();
    
    /*INSERISCI N INTERI NELL'ABR*/
    int i;
    for(i = 0; i < N; i++)
        abr_insert(&tree, get_int());

    /*STAMPA ELEMENTI ALBERO IN ORDINE NON DECRESCENTE (DEB. CRESCENTE)*/
    abr_query(tree);
    
    /*FREE TREE*/
    free_tree(&tree);

    return 0;
}

void abr_query(Tree tree){
    /*VISITA SIMMETRICA DI TREE*/
    if(tree != NULL){
        
        abr_query(tree->left);
        
        printf("%d\n", tree->val);

        abr_query(tree->right);
    }
}

int max(int c1, int c2){
    int cmp = c1 - c2;
    if(cmp <= 0)
        return c2;
    else
        return c1;
}

int get_int(){

    int tmp;
    
    scanf("%d", &tmp);
    scanf("%*[^\n]");
    scanf("%*c");

    return tmp;
}

void abr_insert(Tree* tree_ptr, int val){
    if(tree_ptr != NULL){
        if(*tree_ptr == NULL){
            Node* new_node = alloc_new_node();
            new_node->val = val;
            *tree_ptr = new_node;
        }
        else if(val < (*tree_ptr)->val)
            abr_insert(&((*tree_ptr)->left), val);
        else if(val > (*tree_ptr)->val)
            abr_insert(&((*tree_ptr)->right), val);
        
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


Node* alloc_new_node(){
    
    Node *tmp_node = calloc(1, sizeof(Node));

    if(tmp_node == NULL)
        mem_err();

    return tmp_node;
}

void mem_err(){
    puts("Memoria heap esaurita!");
    exit(EXIT_FAILURE);
}
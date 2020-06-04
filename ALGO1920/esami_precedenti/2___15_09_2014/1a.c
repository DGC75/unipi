#include <stdio.h>
#include <stdlib.h>

/*Tree Definitions*/

typedef struct node{
    int val;
    struct node* left;
    struct node* right;
} Node;

typedef Node* Tree;

/*---*/

/*Tree functions declaration*/

Node*   alloc_new_node();
void    abr_insert(Tree* tree_ptr, int val);
void    free_tree(Tree* tree_ptr);

/*---*/


/*Helpers declaration*/

void    mem_err();
int     get_int();


/*Custom functions*/

void abr_query(Tree);
int L(Node*, int);
int R(Node*, int);


int main(){
    Tree tree = NULL;

    /*LEGGI N*/
    int N = get_int();
    
    /*INSERISCI N INTERI NELL'ABR*/
    int i;
    for(i = 0; i < N; i++)
        abr_insert(&tree, get_int());

    /*STAMPA IN ORDINE CRESCENTE TUTTU I NODI u CHE VERIFICANO LA PROPRIETA':*/
    /*L(u) > R(u)*/
    abr_query(tree);

    /*DEALLOCA ALBERO*/
    free_tree(&tree);

    return 0;        
}

void abr_query(Tree tree){
    /*VISITA SIMMETRICA*/
    if(tree != NULL){
        abr_query(tree->left);

        if(L(tree, 0) > R(tree, 0))
            printf("%d\n", tree->val);

        abr_query(tree->right);
    }
}

int L(Node* u, int sum){
    
    if(u == NULL)
        return sum;
    
    return L(u->left, sum + 1);
}

int R(Node* u, int sum){
    
    if(u == NULL)
        return sum;
    
    return R(u->right, sum + 1);
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
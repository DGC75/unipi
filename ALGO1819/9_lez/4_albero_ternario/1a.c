#include <stdio.h>
#include <stdlib.h>

typedef struct node{
    
    int val;
    struct node* left;
    struct node* center;
    struct node* right;
}Node;

typedef Node* Ternary_tree;

void    mem_err();
int     get_int();
Node*   alloc_node();
void    tree_insert(Ternary_tree *tree_ptr, int val);
void    free_tree(Ternary_tree *tree_ptr);
int     tree_query(Ternary_tree tree);


int main(){

    Ternary_tree tree = NULL;

    /*LEGGI N*/
    int N = get_int();

    /*INSERISCI N ELEMENTI NELL'ALB. TERNARIO*/
    int i;
    for(i = 0; i < N; i++)
        tree_insert(&tree, get_int());

    /*CALCOLA E STAMPA IL NUMERO DI NODI DELL'ALBERO*/
    /*CHE HANNO 3 FIGLI*/
    printf("%d\n", tree_query(tree));

    /*FREE DELL'ALBERO*/
    free_tree(&tree);

    return 0;
}

int tree_query(Ternary_tree tree){
    
    /*CALCOLA E STAMPA IL NUMERO DI NODI DELL'ALBERO*/
    /*CHE HANNO 3 FIGLI*/

    if(tree == NULL)
        return 0;
    else if (tree->left != NULL && tree->center != NULL && tree->right != NULL)
        return 1 + tree_query(tree->left) + tree_query(tree->center) + tree_query(tree->right);
    else
        return tree_query(tree->left) + tree_query(tree->center) + tree_query(tree->right);
}

void mem_err(){
    puts("memoria heap esaurita.");
    exit(EXIT_FAILURE);
}

int get_int(){
    
    int tmp;
    
    scanf("%d", &tmp);
    scanf("%*[^\n]");
    scanf("%*c");

    return tmp;
}

Node* alloc_node(){

    Node *tmp_node = calloc(1, sizeof(Node));
    
    if(tmp_node == NULL)
        mem_err();
    
    return tmp_node;

}

void tree_insert(Ternary_tree *tree_ptr, int val){
    if(tree_ptr != NULL){

        if(*tree_ptr == NULL){
            
            Node* new_node = alloc_node();
            new_node->val = val;

            *tree_ptr = new_node;
        }
        else{
            if(val < (*tree_ptr)->val)
                tree_insert(&((*tree_ptr)->left), val);
            else if(val % (*tree_ptr)->val == 0)
                tree_insert(&((*tree_ptr)->center), val);
            else
                tree_insert(&((*tree_ptr)->right), val);            
        }
    }
}

void free_tree(Ternary_tree *tree_ptr){
    if((tree_ptr != NULL) && (*tree_ptr != NULL)){
        
        free_tree(&((*tree_ptr)->left));
        free_tree(&((*tree_ptr)->center));
        free_tree(&((*tree_ptr)->right));

        free(*tree_ptr);
        *tree_ptr = NULL;
    }
}

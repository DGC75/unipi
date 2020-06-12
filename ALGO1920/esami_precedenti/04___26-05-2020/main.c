#include <stdio.h>
#include <stdlib.h>
#include <math.h>

typedef struct node{
    int val;
    int color;
    struct node* left;
    struct node* right;
} Node;

typedef Node* Tree;

Node*   alloc_new_node();
void    mem_err();
int     get_int();
void    abr_insert(Tree* tree_ptr, int valm, int col);
void    free_tree(Tree* tree_ptr);

int max(int a, int b){
    if((a - b) >=0)
        return a;
    
    return b;
}

int r_height(Node* node,int par){
    
    if(node == NULL)
        return par;
    else
        return max(r_height(node->right, par + !(node->color) ), r_height(node->left, par + !(node->color)));
}

int abr_query(Tree ab, int red_above){

    /*CALCOLA L'ALTEZZA ROSSA DELL'ALBERO AB*/
    /*SE UN SOTTOALBERO VIOLA LA PROPRIETA' INDICATA, RITORNA -1*/
    if(ab == NULL)
        return red_above;
    else if(ab->left == NULL && ab->right == NULL)
        return red_above + !(ab->color);
    
    /*CALCOLA SOTTOSOLUZIONI*/
    int height_node = red_above + !(ab->color);
    int h_left  = abr_query(ab->left, height_node);
    int h_right = abr_query(ab->right, height_node);


     if(abs(h_left - h_right) <= 1)
        return max(h_right, h_left);
    else
        return -1;


}


int main(){

    Tree tree = NULL;
    /*LEGGI N*/
    int N = get_int();
    /*INSERISCI N NODI NELL'ALBERO*/
    int i, val, col;
    for(i=0; i<N; i++){
        val = get_int();
        col = get_int();
        abr_insert(&tree, val, col);
    }
    /*VERIFICA PROPRIETA' DELL'ALBERO*/
    if(abr_query(tree, 0) == -1)
        puts("FALSE");
    else
        puts("TRUE");
    
    /*DEALLOCA ALBERO*/
    free_tree(&tree);

    return 0;
}

int get_int(){

    int tmp;
    
    scanf("%d", &tmp);
    scanf("%*[^\n]");
    scanf("%*c");

    return tmp;
}

void abr_insert(Tree* tree_ptr, int val, int col){
    if(tree_ptr != NULL){
        if(*tree_ptr == NULL){
            Node* new_node = alloc_new_node();
            new_node->val = val;
            new_node->color = col;
            *tree_ptr = new_node;
        }
        else if(val < (*tree_ptr)->val)
            abr_insert(&((*tree_ptr)->left), val, col);
        else if(val > (*tree_ptr)->val)
            abr_insert(&((*tree_ptr)->right), val, col);
        
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

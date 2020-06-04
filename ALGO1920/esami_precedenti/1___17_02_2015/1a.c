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
void post_order_visit(Tree tree, int sum, int min, int *, int*);


int main(){

    Tree tree = NULL;

    /*LEGGI N*/
    int N = get_int();
    
    /*INSERISCI N INTERI NELL'ABR*/
    int i;
    for(i = 0; i < N; i++)
        abr_insert(&tree, get_int());

    /*TROVA IL CAMMINO DI SOMMA MASSIMA E STAMPA IL NODO PIU' PICCOLO APPARTENENTE AD ESSO*/

    int actual_sum = 0, 
        actual_min = 0;

    post_order_visit(tree, 0, 0, &actual_sum, &actual_min);
    printf("%d\n", actual_min);

    /*DEALLOCA ALBERO*/
    free_tree(&tree);

    return 0;
}


void post_order_visit(Tree tree, int sum, int min, int *act_sum, int *act_min){

    if(tree != NULL){
        if(min > tree->val || min == 0){
            min = tree->val;
        }
        if(*act_sum <= sum){
            if(*act_sum < sum){
                *act_sum = sum;
                *act_min = min;
            }

            if(*act_min > min || act_min == 0){
                *act_min = min;
            }

        }
        post_order_visit(tree->left, sum + tree->val, min, act_sum, act_min);
        post_order_visit(tree->right, sum + tree->val, min, act_sum, act_min);
        if(tree->left == NULL && tree->right == NULL){
            if(min > tree->val || min == 0)
                min = tree->val;
        
            sum += tree->val;
        }
    }
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
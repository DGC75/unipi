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
int     abr_query(Tree abr_1, Tree abr_2, int k);
void    free_tree(Tree* tree_ptr);

int main(){

    /*LEGGI N E K*/
    
    int N, K;
    
    scanf("%d%*[ ]%d", &N, &K);
    scanf("%*[^\n]");
    scanf("%*c");
    
    Tree ABR_1 = NULL, ABR_2 = NULL;

    /*ACQUSISCI ABR_1*/
    int i;
    for(i = 0; i < N; i++)
        abr_insert(&ABR_1, get_int());

    /*ACQUISISCI ABR_2*/
    for(i = 0; i < N; i++)
        abr_insert(&ABR_2, get_int());
    
    /*CONTROLLA CHE LA SEQUENZA PER ARRIVARE A K*/
    /*SIA LA STESSA O NO.*/
    printf("%d\n", abr_query(ABR_1, ABR_2, K));

    /*FREE DEGLI ALBERI*/
    free_tree(&ABR_1);
    free_tree(&ABR_2);

    return 0;
}

int abr_query(Tree abr_1, Tree abr_2, int k){
    
    Node *path_1, *path_2;
    path_1 = abr_1;
    path_2 = abr_2;

    while ( (path_1->val == path_2->val) && (path_1 ->val != k)  ){

        if(k < path_1->val)
            path_1 = path_1->left;
        else if(k > path_1->val)
            path_1 = path_1->right;

        if(k < path_2->val)
            path_2 = path_2->left;
        else if(k > path_2->val)
            path_2 = path_2->right;
    }

    if(path_1->val != path_2->val)
        return 0;
    else
        return 1;
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
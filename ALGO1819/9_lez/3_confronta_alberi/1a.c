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

    /*ACQUISISCI ABR_2*/

    /*CONTROLLA CHE LA SEQUENZA PER ARRIVARE A K*/
    /*SIA LA STESSA O NO.*/

    /*FREE DEGLI ALBERI*/

    return 0;
}
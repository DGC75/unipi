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
void    abr_query(Tree tree, int val, int h);
void    free_tree(Tree* tree_ptr);



int main(){

    Tree tree = NULL;
    /*LEGGI N*/
    int N = get_int();
    /*INSERISCI N ELEMENTI NELL'ABR*/
    int i;
    for(i = 0; i < N; i++)
        abr_insert(&tree, get_int());


    /*LEGGI ALL'INFINITO DELLE RICHIESTE, RISPONDENDO ADEGUATAMENTE*/
    /*ESCI SOLO SE IL NUMERO INSERITO E' < 0*/
    int val = get_int();
    while(val >= 0){
        abr_query(tree, val, 0);
        val = get_int();
    }

    /*FREE TREE*/
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
void abr_query(Tree tree, int val, int h){
    /*SE VAL SI TROVA NELL'ALBERO STAMPA PROFONDITA'*/
    /*ALTRIMENTI STAMPA 'NO'*/

    if(tree == NULL){
        puts("NO");
        return;
    }

    int cmp =  val - tree->val;

    if(cmp == 0)
        printf("%d\n", h);
    else if(cmp < 0)
        abr_query(tree->left, val, ++h);
    else if(cmp > 0)
        abr_query(tree->right, val, ++h);
}


void free_tree(Tree* tree_ptr){
    if(tree_ptr != NULL && *tree_ptr != NULL){
        free_tree(&((*tree_ptr)->left));
        free_tree(&((*tree_ptr)->right));
        free(*tree_ptr);
        *tree_ptr = NULL;
    }
}


Node*   alloc_new_node(){
    
    Node *tmp_node = calloc(1, sizeof(Node));

    if(tmp_node == NULL)
        mem_err();

    return tmp_node;
}

void mem_err(){
    puts("Memoria heap esaurita!");
    exit(EXIT_FAILURE);
}
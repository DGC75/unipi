#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct _node{
    int key;/*  Chiave  */
    struct  _node *left;/*  Sottoalbero  sinistro  */
    struct  _node *right;/*  Sottoalbero  destro  */
} Node;

typedef Node* Tree;


void print_t(Tree t){
    if(t != NULL){
        print_t(t->left);
        printf("%d\n", t->key);
        print_t(t->right);
    }
}

int get_int();
void mem_err();
void abr_insert(Tree* t_ptr, int val);
int abr_query(Tree t);
void free_tree(Tree* t_ptr);

int main(){

    Tree t = NULL;

    /*LEGGI N*/
    int N = get_int();

    /*INSERISCI N INTERI NELL'ALBERO*/
    int i;
    for(i = 0; i < N; i++)
        abr_insert(&t, get_int());
    
    /*TROVA IL SECONDO EL. PIU' GRANDE NELL'ALBERO*/
    /*E STAMPALO*/

    printf("%d\n", abr_query(t));

    /*DEALLOCA ALBERO*/
    free_tree(&t);

    return 0;
}
    
int abr_query(Tree t){
    if(t->left == NULL && (t->right->left == NULL && t->right->right == NULL))
        return t->key;
    else if(t->right == NULL && (t->left->left == NULL && t->left->right == NULL))
        return t->left->key;


    Node* prec;
    Node* curr;

    if(t->right == NULL){
        prec = t->left;
        curr = t;
    }
    else{
        prec = t;
        curr = t->right;
    }
    
    while(curr->right != NULL){
        prec = curr;
        curr = curr->right;
    }
    if(curr->left != NULL){
        prec = curr->left;
        while(prec->right != NULL)
            prec = prec->right;
    }
    return prec->key;
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

        if(val < (*t_ptr)->key)
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
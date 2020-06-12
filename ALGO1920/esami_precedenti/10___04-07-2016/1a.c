#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef  struct n{
    int key;
    struct n* left;
    struct n* right;
} Node;

typedef Node* Tree;

int get_int();
void mem_err();
void abr_insert(Tree* t_ptr, int val);
void free_tree(Tree* t_ptr);
int lca(Node* root , int y, int x);

int main(){

    Tree t = NULL;

    int N = get_int();
    
    int i;
    for(i = 0; i < N; i++)
        abr_insert(&t, get_int());
    
    
    printf("%d\n", lca(t, get_int(), get_int()));

    free_tree(&t);

    return 0;
}

int lca(Node* root , int y, int x){
    
    /*TEMPO DI ESECUZIONE: O(2*log(n))*/
    
    Node* lca = root;
    Node* x_p = root;
    Node* y_p = root;

    while(x_p == y_p){
        if(x > x_p->key && y > y_p->key){
            x_p = x_p->right;
            y_p = y_p->right;
            lca = lca->right;
        }
        else if(x < x_p->key && y < y_p->key){
            x_p = x_p->left;
            y_p = y_p->left;
            lca = lca->left;
        }
        else if(x > x_p->key && y < y_p->key){
            x_p = x_p->right;
            y_p = y_p->left;
        }
        else{
            x_p = x_p->left;
            y_p = y_p->right;            
        }
    }

    return lca->key;

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
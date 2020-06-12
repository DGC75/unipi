#include <stdio.h>
#include <stdlib.h>


typedef struct node{
    int key;
    struct node *left;
    struct node *right;
} Node;

typedef Node* Tree;

void insert_tree(Tree *tree_ptr, int val);
int  get_int();
void mem_err();
void print_h_node(Tree tree, int h);
Node* sec_alloc_new_node();
void free_tree(Tree *tree_ptr);


int main(){
    /*CREO STRUTTURA DATI: ALBERO*/
    Tree new_tree = NULL;
    /*ACQUISISCO n INTERI, E LI METTO NELL'ALBERO*/
    int n = get_int();

    int i;
    for(i = 0; i < n; i++)
        insert_tree(&new_tree, get_int());
    
    /*ACQUISISCO k*/
    int h = get_int();
    /*STAMPO TUTTI GLI INTERI DI LIVELLO k*/
    print_h_node(new_tree, h);

    /*FREE TREE*/
    free_tree(&new_tree);

    return 0;
}

/*INSERT INEFFICIENTE, DA RISCRIVERE*/
void insert_tree(Tree *tree_ptr, int val){

    Node *new_node = sec_alloc_new_node();

    new_node->key = val;

    if(tree_ptr != NULL){
        if(*tree_ptr == NULL){
            *tree_ptr = new_node;
        }
        else{
            if(val < (*tree_ptr)->key){
                if((*tree_ptr)->left != NULL){
                    insert_tree( &((*tree_ptr)->left), val);
                    free(new_node);
                }
                else
                    (*tree_ptr)->left = new_node;
            }
            else if (val > (*tree_ptr)->key){
                if((*tree_ptr)->right != NULL){
                    insert_tree( &((*tree_ptr)->right), val);
                    free(new_node);
                }
                else
                    (*tree_ptr)->right = new_node;               
            }
        }
    }
}

Node* sec_alloc_new_node(){
    Node *newNode = calloc(1, sizeof(Node));
    if(newNode == NULL)
        mem_err();

    return newNode;
}

int  get_int(){
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

void print_h_node(Tree tree, int h){
    
    if(tree != NULL){
        if( h == 0){
            printf("%d\n", tree->key);
        }
        else if( h > 0){
            print_h_node(tree->left, h - 1);
            print_h_node(tree->right, h - 1);               
        }
    }
}

void free_tree(Tree *tree_ptr){

        if(tree_ptr != NULL && (*tree_ptr) != NULL){
            free_tree( &((*tree_ptr)->left));
            free_tree( &((*tree_ptr)->right));

            free(*tree_ptr);
        }
}
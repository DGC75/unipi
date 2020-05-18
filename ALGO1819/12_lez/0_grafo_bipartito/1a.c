#include <stdio.h>
#include <stdlib.h>

typedef struct node_lst{
    int label;
    struct node_lst* next;
}Node_lst;

typedef Node_lst* List;

typedef enum {WHITE, RED, BLUE} Color;

typedef struct node{
    Color color;
    int dim;
    int* adj_arr;
} Node;

typedef Node* Graph;

typedef Node* Queue;

Graph load_graph();
int   is_bipartite(Graph graph, Color color);
void  free_graph(Graph* graph_ptr);
Graph alloc_graph(int dim);
int*  alloc_arr(int dim);
void  mem_err();
void  enqueue(Queue* queue_ptr, Node node, Color prec_color);
Node* dequeue(Graph* graph_ptr); 

int main(){
    
    /*CARICA GRAFO IN MEMORIA*/
    /*SETTA IL COLORE DI OGNI NODO A BIANCO*/
    Graph graph = load_graph();

    /*CALCOLA E STAMPA SE IL GRAFO E' BIPARTITO O MENO*/
    printf("%d\n", is_bipartite(graph, RED));

    /*FREE GRAPH*/
    free_graph(&graph);

    return 0;
}

int   is_bipartite(Graph graph, Color prec_color){
        /*FAI UNA BFS SUL GRAFO:*/

        Queue new_queue = NULL;
        enqueue(&new_queue, graph[0], prec_color);

        while(new_queue != NULL){
            Node *u = dequeue(&new_queue);

            int i;
            for(i = 0; i < u->dim; i++){
                Color next_color = (u->color == RED ? BLUE : RED); 
                enqueue(&new_queue, *u, next_color);
            }

            free_graph(&u);
        }
        /*SETTA IL NODO DI PARTENZA DI COLORE: ROSSO*/
        /*OGNI VOLTA CHE VISITI UN NODO*/
        /*SE DI COLORE BIANCO*/ 
            /*LO SI COLORA DEL COLORE OPPOSTO AL PADRE*/
        /*SE IL COLORE E' DIVERSO DAL BIANCO*/
            /*SE IL COLORE E' UGUALE A QUELLO DEL PADRE*/
                /*ESCI E RITORNA ZERO*/
            /*ALTRIMENTI, NON FARE NULLA*/
        
    
}

Graph load_graph(){
    
    int num_nodes;
    scanf("%d", &num_nodes);
    scanf("%*[^\n]");
    scanf("%*c");

    Graph new_graph = alloc_graph(num_nodes);
    
    /*ACQUIRE EACH NODE*/
    int i, j;
    int adj_dim;
    for(i = 0; i < num_nodes; i++){
        
        scanf("%d%*[ ]", &adj_dim);
        new_graph[i].color = WHITE;
        new_graph[i].adj_arr = alloc_arr(adj_dim);
        new_graph[i].dim = adj_dim;

        /*LOAD ADJ ARRAY*/
        for(j = 0; j < adj_dim; j++)
            scanf("%d%*[ ]", &new_graph[i].adj_arr[j]);

        /*CLEAN BUFFER ROW*/
        scanf("%*[^\n]");
        scanf("%*c");
    }

    return new_graph;
}

Graph alloc_graph(int dim){
    Node* tmp = calloc(dim, sizeof(Node));
    
    if(tmp == NULL)
        mem_err();

    return tmp;
}

int*  alloc_arr(int dim){
    int* tmp = calloc(dim, sizeof(int));
    
    if(tmp == NULL)
        mem_err();

    return tmp;
}

void  free_graph(Graph* graph_ptr){
    return;
}

void mem_err(){
    puts("memoria heap esaurita.");
    exit(EXIT_FAILURE);
}
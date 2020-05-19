#include <stdio.h>
#include <stdlib.h>


/*GRAPH DEFINITIONS*/

typedef struct {
    int *edges;
    int dim_edges;
}Node;

typedef Node* Graph;

/*QUEUE DEFINITIONS*/

typedef struct{
    
    int dim;
    int *edges;
    int last_occupied_position;

}Queue;

/*MISCELLANEOUS DEFINITIONS*/

typedef enum {WHITE, GRAY, BLACK} Color;

/*GRAPH METHODS*/

Graph   load_graph  (int dim);
Graph   alloc_graph (int dim);
void    free_graph  (Graph *graph_ptr, int dim);
void    dfs         (Graph graph, int dim, int start_node);
void    dfs_visit   (Graph graph, int dim, int *colors, int node_name);

/*QUEUE METHODS*/

void enqueue        (Queue *queue_ptr, int val);
int  dequeue        (Queue *queue_ptr);
void free_queue     (Queue *queue_ptr);


/*MISCELLANEOUS MEHODS*/

int  get_int        ();
int* alloc_arr      (int dim);
void mem_err        ();



int main(){

    /*ACQUISISCI GRAFO IN MEMORIA*/
    int dim = get_int();
    Graph graph = load_graph(dim);

    /*VISITA DFS*/

    dfs(graph, dim, 3);


    /*DEALLOCA GRAFO*/
    free_graph(&graph, dim);

    return 0;
}

Graph load_graph(int dim){

    Graph new_graph = alloc_graph(dim);
    
    int i;
    for(i = 0; i < dim; i++){

        scanf("%d%*[ ]", &(new_graph[i].dim_edges));
        new_graph[i].edges = alloc_arr(new_graph[i].dim_edges);

        int j;
        for(j=0; j < new_graph[i].dim_edges; j++)
            scanf("%d%*[ ]", &(new_graph[i].edges[j]));
        
        scanf("%*[^\n]");
        scanf("%*c");
    }


    return new_graph;
}

Graph alloc_graph (int dim){
    
    Graph tmp = calloc(dim, sizeof(Node));

    if(tmp == NULL)
        mem_err();

    return tmp;

}

void    free_graph  (Graph *graph_ptr, int dim){
    return;
}

void dfs(Graph graph, int dim, int start_node){
    
    /*COLORA TUTTI I NODI DI BIANCO*/
    int *colors = alloc_arr(dim);
    
    int i;
    for(i = 0; i < dim; i++){
        if(colors[i] == WHITE){
            dfs_visit(graph, dim, colors, (start_node + i)%dim);
        }
    }


    free(colors);
    colors = NULL;
}


void dfs_visit(Graph graph, int dim, int *colors, int node_name){


    printf("Name: %d\n", node_name);
    colors[node_name] = GRAY;
    
    int i;
    /*ISPEZIONA LISTA DI ADIACENZA*/
    for(i = 0; i < graph[node_name].dim_edges; i++){
        /*SE UN NODO RISULTA INESPLORATO, ESPLORALO*/
        if(colors[graph[node_name].edges[i]] == WHITE)
            dfs_visit(graph, dim, colors, graph[node_name].edges[i]);

    }

    /*SETTA IL COLORE A NERO*/
    colors[node_name] = BLACK;
}


int get_int(){

    int tmp;
    scanf("%d", &tmp);
    return tmp;
}

void mem_err(){
    puts("memoria heap esaurita.");
    exit(EXIT_FAILURE);
}

int* alloc_arr(int dim){

    int *tmp = calloc(dim, sizeof(int));
    
    if(tmp == NULL)
        mem_err();

    return tmp;
}
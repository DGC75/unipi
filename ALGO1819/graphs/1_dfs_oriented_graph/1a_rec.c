#include <stdio.h>
#include <stdlib.h>

typedef enum {WHITE, BLACK} Color;

typedef struct {
    int num_edges;
    int *edges;
} Node;

typedef Node* Graph;


int get_int();
void mem_err();
Graph load_graph(int dim);
Graph alloc_graph(int dim);
void  free_graph(Graph *graph_ptr, int dim);
int *alloc_arr(int dim);
void dfs(Graph graph, int dim, int start_node);
void recursive_dfs(Graph graph, int start_node, int *colors);


int main(){

    /*ALLOCA GRAFO*/
    int dim = get_int();
    Graph graph = load_graph(dim);
    
    /*VISITA E STAMPA I NODI CON UNA DFS*/
    dfs(graph, dim, 3);

    /*DEALLOCA GRAFO*/
    free_graph(&graph, dim);
    return 0;
}

void dfs(Graph graph, int dim, int start_node){
    
    /*ALLOCO E INIZIALIZZO L'ARRAY DEI COLORI*/
    int *colors = alloc_arr(dim);

    /*CHIAMO LA DFS RICORSIVAMENTE*/
    recursive_dfs(graph, start_node, colors);

    /*DEALLOCO E INIZIALIZZO L'ARRAY DEI COLORI*/
    free(colors);
    colors = NULL;
}

void recursive_dfs(Graph graph, int start_node, int* colors){
    
    printf("NODE: %d\n", start_node);
    int dest;
    int i;
    for(i = 0; i < graph[start_node].num_edges; i++){
        
        dest = graph[start_node].edges[i];
        if(colors[dest] == WHITE){
            colors[dest] = BLACK;
            recursive_dfs(graph, dest, colors);
        }
    }
}

void free_graph(Graph *graph_ptr, int dim){
    
    if(graph_ptr != NULL){
        int i;
        for(i = 0; i < dim; i++){
            free((graph_ptr[i])->edges);
            (graph_ptr[i])->edges = NULL;
        }
        free(graph_ptr);
        *graph_ptr = NULL;
    }
}

Graph load_graph(int dim){

    Graph new_graph = alloc_graph(dim);

    int i;
    for(i = 0; i < dim; i++){

        scanf("%d%*[ ]", &(new_graph[i].num_edges));
        new_graph[i].edges = alloc_arr(new_graph[i].num_edges);

        int j;
        for(j = 0; j < new_graph[i].num_edges; j++)
            scanf("%d%*[ ]", &(new_graph[i].edges[j]));
        
        scanf("%*[^\n]");
        scanf("%*c");
    }

    return new_graph;    
}

Graph alloc_graph(int dim){

    Graph tmp = calloc(dim, sizeof(Node));
    if(tmp == NULL)
        mem_err();
    
    return tmp;
}

int* alloc_arr(int dim){
    int *tmp = calloc(dim, sizeof(int));

    if(tmp == NULL)
        mem_err();

    return tmp;
}

int get_int(){
    int tmp;
    scanf("%d", &tmp);
    scanf("%*[^\n]");
    scanf("%*c");
    return tmp;
}

void mem_err(){
    puts("memoria heap esaurita.");
    exit(EXIT_FAILURE);
}
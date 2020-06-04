#include <stdio.h>
#include <stdlib.h>

typedef enum{WHITE, BLACK} Color;

typedef struct{
    int num_edges;
    int *edges;
} Node;

typedef Node* Graph;

void mem_err();
int get_int();
int *alloc_arr(int dim);
Graph load_graph(int dim);
Graph alloc_graph(int dim);
void dfs(Graph graph, int dim, int start_node);
void free_graph(Graph *graph_ptr, int dim);

int main(){

    /*ALLOCA GRAFO*/
    int dim = get_int();
    Graph graph = load_graph(dim);

    /*VISITA E STAMPA CON DFS ITERATIVA*/
    dfs(graph, dim, 3);

    /*DEALLOCA GRAFO*/
    free_graph(&graph, dim);

    return 0;
}

void dfs(Graph graph, int dim, int start_node){

    /*ARRAY COLORI INIZIALIZZATO A WHITE CON CALLOC*/
    int *colors = alloc_arr(dim);

    int *stack = alloc_arr(dim);
    int stack_size;
    int src, dest;
    
    colors[start_node] = BLACK;
    stack[0] = start_node; 
    stack_size = 1;

    int i;
    while(stack_size == 1){
        src = stack[--stack_size];
        for(i = 0; i < graph[src].num_edges; i++){
            dest = graph[src].edges[i];
            if(colors[dest] == WHITE){
                colors[dest] = BLACK;

                stack[stack_size ++] = dest; 
            }
        }
    }

    free(colors);
    colors = NULL;
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

    Graph graph = alloc_graph(dim);

    int i;
    for(i = 0; i < dim; i++){
        scanf("%d%*[ ]", &(graph[i].num_edges));

        int j;
        for(j = 0; j < graph[i].num_edges; j++)
            scanf("%d%*[ ]", &(graph[i].edges[j]));


        scanf("%*[^\n]");
        scanf("%*c");
    }

    return graph;

}

Graph alloc_graph(int dim){

    Graph tmp = calloc(dim, sizeof(Node));

    if(tmp == NULL)
        mem_err();

    return tmp;
}

int *alloc_arr(int dim){
    int * tmp = calloc(dim, sizeof(int));

    if(tmp == NULL)
        mem_err();

    return tmp;
}

void mem_err(){
    puts("memoria heap esaurita.");
    exit(EXIT_FAILURE);
}

int get_int(){
    int tmp;
    scanf("%d", &tmp);

    return tmp;
}
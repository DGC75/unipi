#include <stdio.h>
#include <stdlib.h>

typedef enum{WHITE, BLACK} Color;

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

int is_connected(Graph graph, int dim);
int dfs(Graph graph, int start_node, int visited);

int main(){

    /*CARICA GRAFO IN MEMORIA*/
    int dim = get_int();
    Graph graph = load_graph(dim);

    /*VERIFICA E STAMPA SE IL GRAFO E' CONNESSO O MENO*/
    printf("%d\n", is_connected(graph, dim));

    /*DEALLOCA GRAFO*/
    free_graph(&graph, dim);

    return 0;
}

int is_connected(Graph graph, int dim){
    /*VERIFICA CHE CI SIA UN PATH TRA OGNI PAIO DI NODI:*/
    /*POICHE IL GRAFO E' INDIRETTO, POSSO VERIFICARE n-1 COLLEGAMENTI:*/
    /*TRA 0 E 1, TRA 1 E 2, etc. etc., tra n-2 e n-1*/
    /*USARE UNA DFS, E VERIFICARE CHE VISITI TUTTI I NODI DEL GRAFO*/

    int visited = dfs(graph, dim, 0);

    return visited == dim;
}


int dfs(Graph graph, int dim, int start_node){

    /*ARRAY COLORI INIZIALIZZATO A WHITE CON CALLOC*/
    int *colors = alloc_arr(dim);

    int *stack = alloc_arr(dim);
    int stack_size;
    int src, dest;
    
    int visited = 1;

    colors[start_node] = BLACK;
    stack[0] = start_node; 
    stack_size = 1;

    int i;
    while(stack_size /*!=0*/){
        src = stack[--stack_size];
        for(i = 0; i < graph[src].num_edges; i++){
            dest = graph[src].edges[i];
            if(colors[dest] == WHITE){
                colors[dest] = BLACK;
                visited += 1;
                stack[stack_size++] = dest; 
            }
        }
    }

    free(stack);
    stack = NULL;
    free(colors);
    colors = NULL;

    return visited;
}

void free_graph(Graph *graph_ptr, int dim){
    
    if(graph_ptr != NULL){
        int i;
        for(i = 0; i < dim; i++)
            free((*graph_ptr + i)->edges);

        free(*graph_ptr);
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
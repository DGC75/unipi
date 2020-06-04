#include  <stdio.h>
#include  <stdlib.h>

typedef enum {WHITE, BLUE, RED} Color;

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


int is_bipartite(Graph graph, int dim);
int recursive_dfs(Graph graph, int start_node, int* colors, int color);
Color opposite_color(Color color);
int dfs(Graph graph, int dim, int start_node);


int main(){
    /*CARICA GRAFO IN MEMORIA*/
    int dim = get_int();
    Graph graph = load_graph(dim);

    /*VERIFICA E STAMPA SE IL GRAFO E' BIPARTITO O MENO*/
    printf("%d\n", is_bipartite(graph, dim));

    /*DEALLOCA GRAFO*/
    free_graph(&graph, dim);

    return 0;
}


int is_bipartite(Graph graph, int dim){
    /*FAI UNA DFS*/
    /*COLORA IL PRIMO NODO DI UN DETERMINATO COLORE*/
    /*NELLE CHIAMATE RICORSIVE CHIAMALO A COLORI OPPOSTI*/
    /*SE RISULTA CHE UN VERTICE HA LO STESSO COLORE DI UNO ADIACENTE RITORNA 0*/
    /*SE TUTTO PROCEDE BENE, RITORNA 1*/

    return dfs(graph, dim, 0);

}

int recursive_dfs(Graph graph, int start_node, int* colors, int current_color){

    /*    
    printf("NODE: %d\n", start_node);
    printf("NODE color: %d\n", colors[start_node]);
    */

    if(colors[start_node] != WHITE && colors[start_node] != current_color)
        return 0;
    
    colors[start_node] = current_color;

    int i, to;
    for(i = 0; i < graph[start_node].num_edges; i++){
    
        to = graph[start_node].edges[i];
        
        if(colors[to] == WHITE && !recursive_dfs(graph, to, colors, opposite_color(current_color)))
            return 0;

        if (colors[to] != WHITE && colors[to] != opposite_color(current_color))
            return 0;
        
    }

    return 1;

}



Color opposite_color(Color color){
    
    if(color == RED)
        return BLUE;
    else if(color == BLUE)
        return RED;

    return WHITE;
}

int dfs(Graph graph, int dim, int start_node){
    
    /*ALLOCO E INIZIALIZZO L'ARRAY DEI COLORI*/
    int *colors = alloc_arr(dim);
    /*CHIAMO LA DFS RICORSIVAMENTE*/
    int result = recursive_dfs(graph, start_node, colors, BLUE);

    /*DEALLOCO E INIZIALIZZO L'ARRAY DEI COLORI*/
    free(colors);
    colors = NULL;

    return result;
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
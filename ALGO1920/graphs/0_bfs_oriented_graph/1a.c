#include <stdio.h>
#include <stdlib.h>

/*DEFINITIONS*/
/*Graph Definition*/
typedef struct node{
    int num_edges;
    int *edges;
} Node;

typedef Node* Graph;

/*Queue Definition*/
typedef struct queue{
    int *values;
    int last_occupied_place;
    int capacity;
} Queue;


/*METHODS*/
/*Graph Methods*/
int load_graph(Graph *graph_ptr);
Graph alloc_graph(int dim);
void free_graph(Graph *graph_ptr, int dim);

void bfs_visit(Graph graph, int dim, int start_node);

/*Queue methods*/
Queue* alloc_queue(int dim);
void   free_queue(Queue **Queue_ptr,int dim);
void   enqueue(Queue **queue_ptr ,int val);
int    dequeue(Queue **queue_ptr);
int    is_empty(Queue *queue);



/*Helpers*/
int*  alloc_arr(int dim);
void mem_err();



int main(){
    /*LOAD GRAPH ORIENTATO, CON LISTE DI ADIACENZA COMPATTE*/
    Graph new_graph; 
    int dim_graph = load_graph(&new_graph);

    /*VISITA E STAMPA I NODI DI UN GRAFO ORIENTATO*/
    /*TRAMITE VISITA BFS*/
    bfs_visit(new_graph, dim_graph, 3);
   

    /*DEALLOCA GRAFO*/
    free_graph(&new_graph, dim_graph);
   
    return 0;
}

void free_graph(Graph *graph_ptr, int dim){

    if(graph_ptr == NULL || *graph_ptr == NULL)
        return;

    int i;
    for (i = 0; i < dim; i++){
        if((*graph_ptr)[i].edges != NULL){
            free((*graph_ptr)[i].edges);
            (*graph_ptr)[i].edges = NULL;
        }
    }

    free(*graph_ptr);
    *graph_ptr = NULL;
}

void bfs_visit(Graph graph, int dim, int start_node){
    
    int *colors = alloc_arr(dim);

    printf("Nodo %d\n", start_node);
    colors[start_node] = 1;
    Queue *q = alloc_queue(dim);
    
    enqueue(&q, start_node);
    
    int src, i, dest;
    while(!is_empty(q)){
        
        src = dequeue(&q);
        
        for(i = 0; i < graph[src].num_edges; i++){
            /*VISITO L'IESIMO ARCO DEL NODO src*/
            dest = graph[src].edges[i];

            /*SE IL COLORE E'BIANCO*/
            /*SETTALO GRIGIO E INSERISCILO IN CODA*/
            if(!colors[dest]){
                printf("Nodo %d\n", dest);
                colors[dest] = 1;
                enqueue(&q, dest);
            }
        }

    }

    /*DEALLOCA CODA*/
    free_queue(&q, dim);
    free(colors);

}

int load_graph(Graph *graph_ptr){
    
    int nodes;
    scanf("%d", &nodes);
    scanf("%*[^\n]");
    scanf("%*c");

    Graph new_graph = alloc_graph(nodes);
    
    int i;
    for(i = 0; i < nodes; i++){
        

        scanf("%d%*[ ]", &(new_graph[i].num_edges));
        

        new_graph[i].edges = alloc_arr(new_graph[i].num_edges);

        int j;
        for(j = 0; j < new_graph[i].num_edges; j++)
            scanf("%d%*[ ]", &(new_graph[i].edges[j]));    
        

        scanf("%*[^\n]");
        scanf("%*c");
    }

    *graph_ptr = new_graph;

    return nodes;
}

Graph alloc_graph(int dim){
    
    Graph new_graph = calloc(dim, sizeof(Node));
    if(new_graph == NULL)
        mem_err();

    return new_graph;
}

Queue* alloc_queue(int dim){
    
    Queue* new_queue = calloc(1, sizeof(Queue));
    
    new_queue->values = alloc_arr(dim);
    
    new_queue->capacity = dim;

    if(new_queue == NULL)
        mem_err();
    
    return new_queue;
}

void free_queue(Queue **queue_ptr, int dim){
    if(queue_ptr != NULL && *queue_ptr != NULL){
    free((*queue_ptr)->values);
    (*queue_ptr)->values = NULL;
    
    free(*queue_ptr);
    *queue_ptr = NULL;
    }
}

void enqueue(Queue **queue_ptr, int val){
    if(queue_ptr != NULL && *queue_ptr != NULL){
        
        if((*queue_ptr)->last_occupied_place == ((*queue_ptr)->capacity - 1)){
            puts("Queue full. Something went wrong.");
            exit(EXIT_FAILURE);
        }
        else{
            (*queue_ptr)->values[(*queue_ptr)->last_occupied_place] = val;
            (*queue_ptr)->last_occupied_place += 1;   
        }

    }    
    
}

int dequeue(Queue **queue_ptr){
    
    if((*queue_ptr)->last_occupied_place == 0){
        puts("Coda vuota. Something went wrong.");
        exit(EXIT_FAILURE);
    }

    int head = (*queue_ptr)->values[0];
    int i;
    
    for(i = 1; i <= (*queue_ptr)->last_occupied_place; i++)
        (*queue_ptr)->values[i -1] = (*queue_ptr)->values[i];
    
    (*queue_ptr)->values[(*queue_ptr)->last_occupied_place] = 0;
    (*queue_ptr)->last_occupied_place -= 1;

    return head;
}

int is_empty(Queue *queue){
    if(queue->last_occupied_place == 0)
        return 1;
    else
        return 0;
}

int* alloc_arr(int dim){
    
    int* new_arr = calloc(dim, sizeof(int));
    if(new_arr == NULL)
        mem_err();

    return new_arr;
}

void mem_err(){
    puts("memoria heap esaurita");
    exit(EXIT_FAILURE);
}
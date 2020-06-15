#include <stdio.h>
#include <stdlib.h>

typedef struct {
    int num_edges;
    int *edges;
} Node;

typedef Node* Graph;

/*Queue Definition*/
typedef struct _queue{
    /*ARRAY GRANDE QUANTO L'INSIEME DEI VERTICI*/
    int *elements;

    /*NUMERO DI ELEMENTI ATTUALMENTE ALLOCATI*/
    int size;

    /*INDICE DELLA TESTA*/
    int head;

    /*INDICE DELLA CODA*/
    int tail;
}queue;

/*Queue methods*/
void init_queue(queue *Q, int size);
void deinit_queue(queue *Q);
void enqueue(queue *Q, int element);
int  dequeue(queue *Q);



/*Helpers*/
int get_int();
void mem_err();
Graph load_graph(int dim);
Graph alloc_graph(int dim);
void  free_graph(Graph *graph_ptr, int dim);
int *alloc_arr(int dim);

/*Custom*/

int graph_diameter(Graph, int);
int bfs_distance(Graph graph, int dim, int start_node, int end_node);

/*------*/

int main(){
    
    /*CARICA GRAFO IN MEMORIA*/
    int dim = get_int();
    Graph graph = load_graph(dim);
    
    /*CALCOLA E STAMPA IL DIAMETRO DEL GRAFO*/
    printf("%d\n", graph_diameter(graph, dim));
    
    /*DEALLOCA GRAFO*/
    free_graph(&graph, dim);

    return 0;
}

int graph_diameter(Graph graph, int dim){

    /*CALCOLA LA DISTANZA TRA OGNI COPPIA DI NODI, E SALVA QUELLA MAGGIORE*/
    /*NEL MOMENTO IN CUI TROVI 2 NODI CHE NON HANNO UN CAMMINO, STAMPA -1 ED ESCI*/

    int distance = 0, tmp_distance;

    /*PER OGNI COPPIA ORDINATA DI NODI DISTINTI*/
    int i, j;
    for(i = 0; i < dim; i++){
        for(j = 0; j < dim; j++){
            if(i != j){
                
                tmp_distance = bfs_distance(graph, dim, i, j);
                
                if(tmp_distance == -1)
                    return -1;

                if(tmp_distance > distance)
                    distance = tmp_distance;
                
            }
        }
    }

    return distance;
}

int bfs_distance(Graph graph, int dim, int start_node, int end_node){
    
    if (start_node == end_node) 
        return 0;

    int *distance = alloc_arr(dim);
    queue q;
    int src, dest, i;
    
    for(i = 0; i < dim; i++)
        distance[i] = -1;

    distance[start_node] = 0;

    /*INIZIALIZZAZIONE CODA*/
    init_queue(&q, dim);
    enqueue(&q, start_node);


    while(q.head != q.tail){
        
        src = dequeue(&q);
        /*PER OGNI NODO NELLA LISTA DI ADIACENZA DI src*/
        for(i = 0; i < graph[src].num_edges; i++){
            
            dest = graph[src].edges[i];
            /*SE IL NODO NON E'STATO VISITATO, VISITALO E ASSEGNAGLI LA SUA DISTANZA*/
            if(distance[dest] == -1){
            
                distance[dest] = distance[src] + 1;
                /*SE E' UGUALE AD END_NODE, RESTITUISCI LA SUA DISTANZA*/
                if(dest == end_node){
                    int result = distance[dest];
                    deinit_queue(&q);
                    free(distance);
                    return result;
                }
                /*ALTRIMENTI, INSERISCILO IN CODA*/
                enqueue(&q, dest);
            }

        }

    }


    deinit_queue(&q);
    free(distance);
    return -1;
}

void init_queue(queue *Q, int size){
    
    Q->elements = alloc_arr(size);
    Q->size = size;
    Q->head = Q->tail = 0;

}
void deinit_queue(queue *Q){

    free(Q->elements);
    Q->size = 0;
    Q->head = Q->tail = 0;
}

void enqueue(queue *Q, int element){
    Q->elements[Q->tail++] = element;
}

int  dequeue(queue *Q){
    return Q->elements[Q->head++];
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
    new_graph->num_edges = dim;
    

    int i;
    for(i = 0; i < dim; i++){

        scanf("%d", &(new_graph[i].num_edges));
        new_graph[i].edges = alloc_arr(new_graph[i].num_edges);

        int j;
        for(j = 0; j < new_graph[i].num_edges; j++)
            scanf("%d", &(new_graph[i].edges[j]));
        
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
#include <stdio.h>
#include <stdlib.h>
#include <errno.h>
#include <string.h>
#include <pthread.h>
#include <assert.h>

#include <sys/types.h>
#include <unistd.h>


#define N_PRODS 5     /*THREAD PRODUTTORI*/
#define N_CONS 5    /*THREAD CONSUMATORI*/
#define MAX_MSG_LENGTH 300



#define EXIT_MSG "!<@*>KILL<*@>!"


typedef struct _dataNode{
    void *data;
    struct _dataNode *next;
} DataNode;

typedef struct _queue{
  DataNode* head;
  DataNode* tail;
}Queue;

Queue queue;

void init_queue       (Queue *q_ptr);
void enqueue          (Queue *q_ptr, void *data);
void* dequeue         (Queue *q_ptr);

pthread_mutex_t mtx_queue = PTHREAD_MUTEX_INITIALIZER;
pthread_cond_t qIsEmpty = PTHREAD_COND_INITIALIZER;
pthread_cond_t all_msgs_sent = PTHREAD_COND_INITIALIZER;

long sent_exits = 0;
long sent_msgs = 0;
long tot_msgs = 0;


/*MTXS E CVS USATI PER MANDARE GLI ARGS AI PRODS*/
int hbr = 0;
int hbw = 0;
pthread_mutex_t mtx_msgs_per_prod = PTHREAD_MUTEX_INITIALIZER;
pthread_cond_t has_been_read = PTHREAD_COND_INITIALIZER;





/*
// ritorna
//   0: ok
//   1: non e' un numbero
//   2: overflow/underflow
//
*/
int isNumber(const char* s, long* n) {
  char* e= NULL;
  long val;
  if (s==NULL) return 1;
  if (strlen(s)==0) return 1;

  errno=0;
  val = strtol(s, &e, 10);
  if (errno == ERANGE) return 2;    /* overflow*/
  if (e != NULL && *e == (char)0) {
    *n = val;
    return 0;   /* successo*/ 
  }
  return 1;   /*non e' un numero*/
}

void* prod_routine(void *arg){

    long msgs;
    int i;
    char *new_msg = NULL;


    pthread_mutex_lock(&mtx_msgs_per_prod);

    while(!hbw || hbr)
      pthread_cond_wait(&has_been_read, &mtx_msgs_per_prod);
    
    msgs = *(long*)arg;
    
    hbr = 1;
    hbw = 0;
    printf("thread %li: %li msgs\n", pthread_self(), msgs);


    pthread_cond_signal(&has_been_read);
    pthread_mutex_unlock(&mtx_msgs_per_prod);


  
    for(i = 0; i < msgs; i++){

      new_msg = calloc(MAX_MSG_LENGTH, sizeof(char));
      if(new_msg == NULL){
        perror("calloc");
        exit(EXIT_FAILURE);
      }

      sprintf(new_msg, "dal proc %li: %d", pthread_self(), i+1);
      pthread_mutex_lock(&mtx_queue);
      enqueue(&queue, new_msg);
      ++sent_msgs;
      pthread_cond_signal(&qIsEmpty);
      pthread_mutex_unlock(&mtx_queue);
    }



    pthread_mutex_lock(&mtx_queue);

    while (sent_msgs < tot_msgs)
      pthread_cond_wait(&all_msgs_sent, &mtx_queue);

    pthread_mutex_unlock(&mtx_queue);

    while(1){
      pthread_mutex_lock(&mtx_queue);
      if(sent_exits < N_CONS){
        new_msg = calloc(MAX_MSG_LENGTH, sizeof(char));
        if(new_msg == NULL){
          perror("calloc");
          exit(EXIT_FAILURE);
        }
        sprintf(new_msg, EXIT_MSG);
        enqueue(&queue, new_msg);
        ++sent_exits;
        pthread_cond_signal(&qIsEmpty);

      }
      pthread_mutex_unlock(&mtx_queue);
    } 
    

    return NULL;
}

void* cons_routine(void *arg){

  char *msg = NULL; 

  printf("cons %li created\n", pthread_self());
  fflush(stdout);


  while(1){
    pthread_mutex_lock(&mtx_queue);

    while(queue.head == NULL)
      pthread_cond_wait(&qIsEmpty, &mtx_queue);

    msg = dequeue(&queue);
    
    if(msg != NULL){
      if(strncmp(EXIT_MSG, msg, sizeof(EXIT_MSG)) != 0){
        printf("%li received: ", pthread_self());
        puts(msg);
        free(msg);
      }
      else{/*RECEIVED EXIT MSG*/
        free(msg);
        printf("%li got exit msg\n", pthread_self());

        break;
      }
    }

  msg = NULL;
  }

  msg = NULL;
  pthread_mutex_unlock(&mtx_queue);
  return NULL;
}

int main(int argc, char *argv[]){

    int i;
    int err;
    long msgs_per_prod;
    long q, r;
    
    pthread_t arr_prod_ths[N_PRODS]; 
    pthread_t arr_cons_ths[N_CONS];

    if(argc != 2){
        printf("Usage:./%s n_msgs", argv[0]);
        exit(EXIT_FAILURE);
    }

    if(isNumber(argv[1], &tot_msgs)){
        puts("num_messages is not a number");
        exit(EXIT_FAILURE);
    }


    init_queue(&queue); 
    q = tot_msgs/N_PRODS;
    r = tot_msgs%N_PRODS;


    for(i=0; i < N_PRODS; i++){
        msgs_per_prod = ((--r) >= 0)? q + 1: q;
        hbr = 0;
        hbw = 1;

        if((err = pthread_create(arr_prod_ths + i, NULL, prod_routine, &msgs_per_prod)) != 0){
         perror("pthread_create prod");
         exit(EXIT_FAILURE);
        }


        
    }

    /*CREAZIONE THS CONSUMERS*/

    for(i=0; i < N_CONS; i++){
        if((err = pthread_create(arr_cons_ths + i, NULL, cons_routine, NULL)) != 0){
         perror("pthread_create cons");
         exit(EXIT_FAILURE);
        }
    }
    

    /*JOIN VARIE*/
    for(i=0; i < N_PRODS; i++){
        if((err = pthread_join(arr_prod_ths[i], NULL)) != 0){
         perror("pthread_join prods");
         exit(EXIT_FAILURE);
        }
    } 

    for(i=0; i < N_CONS; i++){
        if((err = pthread_join(arr_cons_ths[i], NULL)) != 0){
         perror("pthread_join cons");
         exit(EXIT_FAILURE);
        }
    } 

    return 0;
}

void init_queue(Queue *q_ptr){
  if(q_ptr == NULL){
    puts("init_queue: error, NULL pointer");
    exit(EXIT_FAILURE);
  }

  q_ptr->head = NULL;
  q_ptr->tail = NULL;

  return;
}
void enqueue(Queue *q_ptr, void *data_ptr){
  
  DataNode *newN = calloc(1, sizeof(DataNode)); 
  if(newN == NULL){
      perror("calloc");
      exit(EXIT_FAILURE);
  }

  newN->data = data_ptr;

  if(q_ptr->head == NULL){
    q_ptr->tail = newN;
  }
  else{
    newN->next = q_ptr->head;
  }

  q_ptr->head = newN;
}
void*dequeue(Queue *q_ptr){

  DataNode *tmp_ptr = q_ptr->head;
  void *data;
  
  if(q_ptr == NULL){
    puts("deq: qptr == NULL");
    exit(EXIT_FAILURE);
  }


  if(q_ptr->head == NULL){
    data = NULL;
  }
  else if(q_ptr->head == q_ptr->tail){
    q_ptr->head = q_ptr->tail = NULL;

    data = tmp_ptr->data;
    free(tmp_ptr);
    return data;

  }
  else{
    while (tmp_ptr->next != q_ptr->tail){
      tmp_ptr = tmp_ptr->next;
    }
    q_ptr->tail = tmp_ptr;

    tmp_ptr = tmp_ptr->next;

    q_ptr->tail->next = NULL;

    data = tmp_ptr->data;
    free(tmp_ptr);
  }

  return data;
}


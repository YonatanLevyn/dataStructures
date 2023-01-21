#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>


typedef enum
{
    STACK_CHAR,
    STACK_INT
}datatype;


typedef struct queue
{
    int type_size;
    size_t size;
    void* head;
    void* tail;
}queue;

queue queueCreator(size_t size, datatype type){

    /* Check which datatype we store in order to allocate memory for it*/
    int effectiveSize;
    if (type == STACK_CHAR){
        effectiveSize = sizeof(char);
    } else {
        effectiveSize = sizeof(int);
    }

    /* Creating a queue*/
    queue q = {
        .size = size,
        .type_size = effectiveSize,
        .head = malloc(effectiveSize),
        .tail = NULL
    };
    return q;

}
bool isfull(queue *q) {
  if (q->tail == ((q->size)*(q->type_size)+(q->head))){
    return true;
  }else{
    return false;
  }
}

void insert(queue* q,void* item){
    if (q->tail == NULL){
        memcpy(q->head, item, q->type_size);
        q->tail = q->head;
    }if (isfull(q)){
        printf("%c\n", "the queue is full");
    }else{
        q->tail += q->type_size;
        memcpy(q->tail, item, q->type_size);
    }
}

void extract(queue* q){
    for (int i = 0; i<q->size; i++){
        /*shifting all values to the left: head[i] = head[i+1]*/
        memcpy(q->head + i*(q->type_size), q->head + (i+1)*(q->type_size), q->type_size);
    }
    /*updating the tail position*/
    q->tail -= q->type_size;
}


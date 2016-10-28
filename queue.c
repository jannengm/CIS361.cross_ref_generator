//
// Created by jannengm on 10/28/16.
//

#include "queue.h"

void init_queue(queue_t * q){
    q->front = 0;
    q->back = -1;
}

void enqueue(int n, queue_t * q){
    q->array[ ++(q->back) ] = n;
}

int dequeue(queue_t * q){
    return q->array[ (q->front)++ ];
}

/*Returns 1 if the queue is empty, else 0*/
int is_empty(queue_t * q){
    return q->back < q->front ? 1 : 0;
}
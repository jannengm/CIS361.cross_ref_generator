//
// Created by jannengm on 10/28/16.
//

#include "queue.h"

/*Initializes a queue to be empty*/
void init_queue(queue_t * q){
    q->front = 0;
    q->back = -1;
}

/*Adds an item to the back of the queue*/
void enqueue(int n, queue_t * q){
    if(q->back < MAX_SIZE - 1)
        q->array[ ++(q->back) ] = n;
}

/*Removes the item at the front of the queue and returns it*/
int dequeue(queue_t * q){
    return q->array[ (q->front)++ ];
}

/*Returns 1 if the queue is empty, else 0*/
int is_empty(queue_t * q){
    return q->back < q->front ? 1 : 0;
}

/*Returns the most recently added item*/
int get_back(queue_t * q){
    return q->array[q->back];
}
/*Queue source code. Contains function definitions of functions declared in
 * queue.h*/

#include "queue.h"

/*Takes as arguments a pointer to a queue. Initializes a queue to be empty.*/
void init_queue(queue_t * q){
    q->front = 0;
    q->back = -1;
}

/*Takes as argument a pointer to a queue and an integer. Adds the integer to
 * the back of the queue if the queue is not full.*/
void enqueue(int n, queue_t * q){
    if(q->back < MAX_SIZE - 1)
        q->array[ ++(q->back) ] = n;
}

/*Takes as arguments a pointer to a queue. Removes the item at the front of
 * the queue and returns it.*/
int dequeue(queue_t * q){
    return q->array[ (q->front)++ ];
}

/*Takes as arguments a pointer to a queue. Returns 1 if the queue is empty,
 * else 0*/
int is_empty(queue_t * q){
    return q->back < q->front ? 1 : 0;
}

/*Takes as arguments a pointer to a queue. Returns the most recently added item*/
int get_back(queue_t * q){
    return q->array[q->back];
}
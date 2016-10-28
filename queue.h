//
// Created by jannengm on 10/28/16.
//

#define MAX_SIZE 100

struct queue_t{
    int array[MAX_SIZE];
    int front;
    int back;
};

typedef struct queue_t queue_t;

void init_queue(queue_t * q);
void enqueue(int n, queue_t * q);
int dequeue(queue_t * q);
int is_empty(queue_t * q);



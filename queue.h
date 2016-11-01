/*Queue header file. Contains the struct and function prototypes for a
 * queue of integers*/

/*The maximum size of the queue*/
#define MAX_SIZE 100

/*The queue.*/
struct queue_t{
    int array[MAX_SIZE];
    int front;
    int back;
};

typedef struct queue_t queue_t;

/*Takes as arguments a pointer to a queue. Initializes a queue to be empty.*/
void init_queue(queue_t * q);

/*Takes as argument a pointer to a queue and an integer. Adds the integer to
 * the back of the queue if the queue is not full.*/
void enqueue(int n, queue_t * q);

/*Takes as arguments a pointer to a queue. Removes the item at the front of
 * the queue and returns it.*/
int dequeue(queue_t * q);

/*Takes as arguments a pointer to a queue. Returns 1 if the queue is empty,
 * else 0*/
int is_empty(queue_t * q);

/*Takes as arguments a pointer to a queue. Returns the most recently added item*/
int get_back(queue_t * q);


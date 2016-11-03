/*******************************************************************************
 * CIS 361 System Programming, Fall 2016
 * Project 2 - Cross-Reference Generator
 * Author - Mark Jannenga
 *
 * Linked list header file. Contains the struct and function prototypes for a
 * linked list of identifiers and a queue of the lines eah identifier appears on
*******************************************************************************/

#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <ctype.h>
#include "queue.h"

#define IDENT_LEN 64

/*The data contained in each node of the linked list*/
struct data_t{
    char identifier[IDENT_LEN];
    queue_t lines;
};

/*The nodes that make up a linked list*/
struct node_t{
    struct data_t d;
    struct node_t *next;
};

/*The linked list*/
struct list_t{
    struct node_t* head;
    struct node_t* tail;
};

typedef struct node_t node_t;
typedef struct data_t data_t;
typedef struct list_t list_t;

/*Takes as arguments a string identifier, a line number, and a pointer to a node.
 * Allocates memory for a new node. Initializes new node with passed values.
 * Returns pointer to the new node.*/
node_t* init_node(char* ident, int line, node_t* next);

/*Takes as arguments pointers to two nodes. Returns a value < 0 if the identifier
 * in node_t n comes before node_t m alphabetically, a value > 0 if n comes after
 * m alphabetically, and 0 if the identifiers are equal*/
int compare_node(const node_t * n, const node_t * m);

/*Takes as arguments a pointer to a linked list. Initializes the linked
 * list to be an empty list*/
void init_list(list_t * linked_list);

/*Takes as arguments a pointer to a linked list, a string identifier, and a line number.
 * If the identifier already exists in the linked list, adds the line number to
 * its queue of line numbers. Otherwise it creates a new node and inserts it
 * either at the head of an empty list, or in the correct alphabetical location*/
void add(list_t* linked_list, char * ident, int line);

/*Takes as arguments a pointer to a linked list and a pointer to a node. Inserts a node
 * into the linked list in alphabetical order by identifier*/
void insert_in_order(list_t* linked_list, node_t * n);

/*Takes as arguments  a pointer to a linked list and a string identifier. Searches through
 * the linked list for an identifier, returns a pointer to the node if the identifier
 * is found in the linked list, else NULL*/
node_t* find_identifier(list_t* link_list, char* ident);

/*Takes as arguments a pointer to a linked list. Frees all allocated memory space of
 * nodes in the linked list*/
void free_list(list_t* link_list);

/*Takes as arguments a pointer to a linked list. Prints the identifiers in the linked
 * list and the lines on which they appear.*/
void print_list(list_t * linked_list);
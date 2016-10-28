//
// Created by jannengm on 10/28/16.
//
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <ctype.h>
#include "queue.h"

#define IDENT_LEN 64

struct data_t{
    char identifier[IDENT_LEN];
    queue_t lines;
};

struct node_t{
    struct data_t d;
    struct node_t *next;
};

struct list_t{
    struct node_t* head;
    struct node_t* tail;
};

typedef struct node_t node_t;
typedef struct data_t data_t;
typedef struct list_t list_t;

/*Allocates memory for a new node. Initializes new node with
 *passed values. Returns pointer to the new node.*/
node_t* init_node(char* ident, int line, node_t* next);

/*Initializes the linked list to be an empty list*/
void init_list(list_t * linked_list);

/*Add a node to the end of the linked list*/
void add(list_t* linked_list, char * ident, int line);

/*Searches through the linked list for an identifier, returns
 *a pointer to the node if found, else NULL*/
node_t* find_identifier(list_t* link_list, char* ident);

/*Frees all allocated memory space of nodes in linked list*/
void free_list(list_t* link_list);

void print_list(list_t * linked_list);
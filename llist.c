//
// Created by jannengm on 10/28/16.
//

#include "llist.h"

/*Allocates memory for a new node. Initializes new node with
 *passed values. Returns pointer to the new node.*/
node_t* init_node(char* ident, int line, node_t* next){
    node_t* n = malloc( sizeof(node_t) );
//    n->d.identifier = ident;
    strncpy(n->d.identifier, ident, IDENT_LEN);
    n->d.line = line;
    n->next = next;

    return n;
}

/*Initializes the linked list to be an empty list*/
void init_list(list_t * linked_list){
    linked_list->head = NULL;
    linked_list->tail = NULL;
}

/*Add a node to the end of the linked list*/
void add(list_t* linked_list, char * ident, int line){
    node_t * n = find_identifier(linked_list, ident);
    if(n == NULL){
        n = init_node(ident, line, NULL);
        if (linked_list->head == NULL || linked_list->tail == NULL) {
            linked_list->head = n;
            linked_list->tail = n;
        } else {
            linked_list->tail->next = n;
            linked_list->tail = n;
        }
    }
    else{
        //add line to queue
    }
}

/*Searches through the linked list for an identifier, returns
 *a pointer to the node if found, else NULL*/
node_t* find_identifier(list_t* linked_list, char* ident){
    node_t* n = linked_list->head;
    while( n != NULL ){
        if( strcmp(n->d.identifier, ident) == 0 ){
            break;
        }
        n = n->next;
    }
    return n;
}

/*Frees all allocated memory space of nodes in linked list*/
void free_list(list_t * linked_list){
    node_t* n = linked_list->head;
    node_t* to_free;

    while(n != NULL) {
        to_free = n;
        n = n->next;
        free(to_free);
    }
}

void print_list(list_t * linked_list){
    node_t * tmp = linked_list->head;
    while(tmp != NULL){
        printf("%d\t%s\n", tmp->d.line, tmp->d.identifier);
        tmp = tmp->next;
    }
}


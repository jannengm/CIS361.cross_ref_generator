/*******************************************************************************
 * CIS 361 System Programming, Fall 2016
 * Project 2 - Cross-Reference Generator
 * Author - Mark Jannenga
 *
 * Linked list source file. Contains function definitions of functions declared
 * in llist.h
*******************************************************************************/

#include "llist.h"

/*Takes as arguments a string identifier, a line number, and a pointer to a node.
 * Allocates memory for a new node. Initializes new node with passed values.
 * Returns pointer to the new node.*/
node_t* init_node(char* ident, int line, node_t* next){
    node_t* n = malloc( sizeof(node_t) );
    strncpy(n->d.identifier, ident, IDENT_LEN);
    init_queue( &(n->d.lines) );
    enqueue( line, &(n->d.lines) );
    n->next = next;

    return n;
}

/*Takes as arguments pointers to two nodes. Returns a value < 0 if the identifier
 * in node_t n comes before node_t m alphabetically, a value > 0 if n comes after
 * m alphabetically, and 0 if the identifiers are equal*/
int compare_node(const node_t * n, const node_t * m){
    char n_str[IDENT_LEN];
    char m_str[IDENT_LEN];
    int i;

    /*Make copy of original identifiers, since they are about to be modified*/
    memcpy(n_str, n->d.identifier, IDENT_LEN);
    memcpy(m_str, m->d.identifier, IDENT_LEN);

    /*Make the identifiers all upper case*/
    for(i = 0; i < IDENT_LEN; ++i){
        n_str[i] = (char) toupper(n_str[i]);
        m_str[i] = (char) toupper(m_str[i]);
    }

    /*Compare the identifiers*/
    int r = strcmp(n_str, m_str);

    /*If they are equal when not considering case, return the result of case
     * sensitive comparison, since the same word with different capitalization is
     * a different identifier*/
    if(r == 0){
        return strcmp(n->d.identifier, m->d.identifier);
    }
    else{
        return r;
    }
}

/*Takes as arguments a pointer to a linked list. Initializes the linked
 * list to be an empty list*/
void init_list(list_t * linked_list){
    linked_list->head = NULL;
    linked_list->tail = NULL;
}

/*Takes as arguments a pointer to a linked list, a string identifier, and a line number.
 * If the identifier already exists in the linked list, adds the line number to
 * its queue of line numbers. Otherwise it creates a new node and inserts it
 * either at the head of an empty list, or in the correct alphabetical location*/
void add(list_t* linked_list, char * ident, int line){
    node_t * n = find_identifier(linked_list, ident);

    /*If the node does not exist, create and insert it*/
    if(n == NULL){
        n = init_node(ident, line, NULL);

        /*If the list is empty, initialize it with this node*/
        if (linked_list->head == NULL || linked_list->tail == NULL) {
            linked_list->head = n;
            linked_list->tail = n;
        }

        /*Otherwise, insert in the list in order*/
        else {
            insert_in_order(linked_list, n);
        }
    }

    /*If the identifier already exists and is not a duplicate on
     * that line, add the line number to its queue*/
    else if( get_back( &(n->d.lines) ) != line ){
        enqueue( line, &(n->d.lines) );
    }
}

/*Takes as arguments a pointer to a linked list and a pointer to a node. Inserts a node
 * into the linked list in alphabetical order by identifier*/
void insert_in_order(list_t* linked_list, node_t * n){
    node_t * tmp;

    /*If node n comes before head, insert n at head*/
    if( compare_node(linked_list->head, n) > 0 ){
        n->next = linked_list->head;
        linked_list->head = n;
    }

    /*See if the node falls somewhere in the middle*/
    else {
        for(tmp = linked_list->head; tmp != linked_list->tail; tmp = tmp->next){
            if( compare_node(tmp, n) < 0 && compare_node(tmp->next, n) > 0 ){
                n->next = tmp->next;
                tmp->next = n;
                break;
            }
        }

        /*If made it to the end of the loop without inserting, add at the end*/
        if(tmp == linked_list->tail){
            linked_list->tail->next = n;
            linked_list->tail = n;
        }
    }

}

/*Takes as arguments  a pointer to a linked list and a string identifier. Searches through
 * the linked list for an identifier, returns a pointer to the node if the identifier
 * is found in the linked list, else NULL*/
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

/*Takes as arguments a pointer to a linked list. Frees all allocated memory space of
 * nodes in the linked list*/
void free_list(list_t * linked_list){
    node_t* n = linked_list->head;
    node_t* to_free;

    while(n != NULL) {
        to_free = n;
        n = n->next;
        free(to_free);
    }
}

/*Takes as arguments a pointer to a linked list. Prints the identifiers in the linked
 * list and the lines on which they appear.*/
void print_list(list_t * linked_list){
    node_t * tmp;
    node_t * iter  = linked_list->head;

    /*Loop through each node in the linked list*/
    while(iter != NULL){
        /*dequeue is destructive, so make a copy*/
        tmp = malloc( sizeof(node_t) );
        memcpy(tmp, iter, sizeof(node_t) );

        /*Print the data of the node*/
        printf("%-20s\t", tmp->d.identifier);
        while( !is_empty( &(tmp->d.lines) ) ){
            printf("%d ", dequeue(&(tmp->d.lines)));
        }
        printf("\n");

        iter = iter->next;
        free(tmp);
    }
}


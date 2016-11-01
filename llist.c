//
// Created by jannengm on 10/28/16.
//

#include "llist.h"

/*Allocates memory for a new node. Initializes new node with
 *passed values. Returns pointer to the new node.*/
node_t* init_node(char* ident, int line, node_t* next){
    node_t* n = malloc( sizeof(node_t) );
    strncpy(n->d.identifier, ident, IDENT_LEN);
    init_queue( &(n->d.lines) );
    enqueue( line, &(n->d.lines) );
    n->next = next;

    return n;
}

/*Returns a value < 0 if the identifier in node_t n comes before
 * node_t m alphabetically, a value > 0 if n comes after m alphabetically,
 * and 0 if the identifiers are equal*/
int compare_node(const node_t * n, const node_t * m){
    char n_str[IDENT_LEN];
    char m_str[IDENT_LEN];
    int i;

    memcpy(n_str, n->d.identifier, IDENT_LEN);
    memcpy(m_str, m->d.identifier, IDENT_LEN);

    for(i = 0; i < IDENT_LEN; ++i){
        n_str[i] = (char) toupper(n_str[i]);
        m_str[i] = (char) toupper(m_str[i]);
    }

    int r = strcmp(n_str, m_str);
    if(r == 0){
        return strcmp(n->d.identifier, m->d.identifier);
    }
    else{
        return r;
    }
}

/*Initializes the linked list to be an empty list*/
void init_list(list_t * linked_list){
    linked_list->head = NULL;
    linked_list->tail = NULL;
}

/*Add a node to the end of the linked list (unordered)*/
//void add(list_t* linked_list, char * ident, int line){
//    node_t * n = find_identifier(linked_list, ident);
//    if(n == NULL){
//        n = init_node(ident, line, NULL);
//        if (linked_list->head == NULL || linked_list->tail == NULL) {
//            linked_list->head = n;
//            linked_list->tail = n;
//        } else {
//            linked_list->tail->next = n;
//            linked_list->tail = n;
//        }
//    }
//    else if( get_back( &(n->d.lines) ) != line ){
//        //add line to queue
//        enqueue( line, &(n->d.lines) );
//    }
//}

/*Add a node into an ordered linked list*/
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

/*Insert a node into the linked list in alphabetical order by identifier*/
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
        printf("%-20s\t", tmp->d.identifier);
        while( !is_empty( &(tmp->d.lines) ) ){
            printf("%d ", dequeue(&(tmp->d.lines)));
        }
        printf("\n");
        tmp = tmp->next;
    }
}


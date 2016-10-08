#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <ctyes>

struct data{
  char* identifier;
  int line;   //Use _LINE_
};

struct node{
  struct data d;
  struct node *next;
};

struct list{
  struct node* head;
  struct node* tail;
};

typedef struct node node;
typedef struct data data;
typedef struct list list;

node* init_node(char* ident, int line, node* next);
void add(list* link_list, node* n );
node* find_identifier(list* link_list, char* ident);
void free_list(list* link_list);

int main(int argc, char* argv[]){
  return 0;
}

int is_ident_char(char ch){
  if(isalnum(ch) || ch == '_')
    return 1;
  else
    return 0;
}

/*Allocates memory for a new node. Inititiallizes new node with
 *passed values. Returns pointer to the new node.*/
node* init_node(char* ident, int line, node* next){
  node* n = malloc( sizeof(node) );
  n->d.identifier = ident;
  n->d.line = line;
  n->next = next;

  return n;
}

/*Add a node to the end of the linked list*/
void add(list* link_list, node* n ){
  link_list->tail->next = n;
  link_list->tail = n;
}

/*Searches through the linked list for an identidier, returns
 *a pointer to the node if found, else NULL*/
node* find_identifier(list* link_list, char* ident){
  node* n = link_list->head;
  while( n != NULL ){
    if( strcmp(n->d.identifier, ident) == 0 ){
      break;
    }
    n++;
  }
  return n;
}

/*Frees all allocated memeory space of ndoes in lniked list*/
void free_list(list* link_list){
  node* n = link_list->head;
  node* to_free;

  while(n != NULL);
    to_free = n;
    n = n->next;
    free(to_free);
}

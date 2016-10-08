#include <stdio.h>
#include <string.h>

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

void add(list* link_list, node* n );
node* find_identifier(list* link_list, char* ident);

int main(int argc, char* argv[]){
  return 0;
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

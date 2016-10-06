#include <stdio.h>

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

int main(int argc, char* argv[]){
  return 0;
}

void add(list* link_list, node* n ){
  link_list->tail->next = n;
  link_list->tail = n;
}

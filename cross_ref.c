#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <ctype.h>

#define IDENT_LEN 64
#define LINE_LEN 1024

struct data{
    char identifier[IDENT_LEN];
    int line;
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
    FILE * in_file;
    char buffer[LINE_LEN];
    int line = 1;

    /*Check for correct number of arguments*/
    if(argc != 2){
        fprintf(stderr, "Usage: [%s] [path to file]\n", argv[0]);
        exit(1);
    }

    /*Open specified file*/
    in_file = fopen(argv[1], "r");
    if(in_file == NULL){
        fprintf(stderr, "Failed to open file %s\n", argv[1]);
        exit(1);
    }

    /*Read lines from input*/
    while(fgets(buffer, LINE_LEN, in_file) != NULL && !feof(in_file) && !ferror(in_file)){
//        printf("%d\t%s", line++, buffer);
        //Break line into identifiers
    }

    /*Clean up and exit*/
    fclose(in_file);
    return 0;
}

/*Checks if the passed character is a valid identifier character or not.
 * Returns 1 if true, else 0*/
int is_ident_char(char ch){
    if(isalnum(ch) || ch == '_')
        return 1;
    else
        return 0;
}

/*Allocates memory for a new node. Initializes new node with
 *passed values. Returns pointer to the new node.*/
node* init_node(char* ident, int line, node* next){
    node* n = malloc( sizeof(node) );
//    n->d.identifier = ident;
    strncpy(n->d.identifier, ident, IDENT_LEN);
    n->d.line = line;
    n->next = next;

    return n;
}

/*Add a node to the end of the linked list*/
void add(list* link_list, node* n ){
    if(link_list->tail == NULL || link_list->tail == NULL) {
        link_list->head = n;
        link_list->tail = n;
    }
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

/*Frees all allocated memory space of nodes in linked list*/
void free_list(list* link_list){
    node* n = link_list->head;
    node* to_free;

    while(n != NULL) {
        to_free = n;
        n = n->next;
        free(to_free);
    }
}

void process_line(const char * buf){
    char *tmp, prev_ch = '\0';
    int ignore = 0;

    for(tmp = buf; *tmp != '\n' && *tmp != '\0'; ++tmp){
        if(prev_ch == '/' && *tmp == '/'){
            break;
        }
        prev_ch = *tmp;
    }
}

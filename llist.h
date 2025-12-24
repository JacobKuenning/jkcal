#include <stdlib.h>

typedef struct node {
    void *data; // don't mix stack and heap memory in one linked list!
    struct node *next;
    struct node *prev;
} node;

typedef struct{
    node* head;
    node* tail;
} llist;

llist create_llist(void);

// for use within linked list functions, creates a node holding a void*
node* create_node(void*);

// size of linked list
int size(llist* l);

// add void* to back of linked list
void push_back(llist* l, void* v);

// remove back of linked list
void pop_back(llist* l);

// value in index of linked list
void* at(llist* l, int index);

// value at back of linked list
void* back(llist* l);

// for llists with stack allocated node data
void free_nodes(llist* l);

// for llists with heap allocated node data
void free_data(llist* l);
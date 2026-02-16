#include "llist.h"

llist* create_llist(void){
    llist* l = malloc(sizeof(*l));
    l->head = NULL;
    l->tail = NULL;
    return l;
}

node* create_node(void* v){
    node* n = malloc(sizeof(*n));
    n->next = NULL;
    n->prev = NULL;
    n->data = v;
    return n;
}

int size(llist* l){
    int n = 0;
    node* currNode = l->head;
    while (currNode != NULL){
        currNode = currNode->next;
        n++;
    }
    return n;
}

void push_back(llist *l, void *v) {
    node* n = create_node(v);
    if (l->tail) {   // if list is not empty
        l->tail->next = n;
        n->prev = l->tail;
    } else {         // empty list
        l->head = n;
    }

    l->tail = n;
}

void insert(llist* l, int n, void* v){
    node* new_node = create_node(v);
    if (is_empty(l)) return;
    if (n >= size(l) + 1){
        push_back(l, v); return;
    } 
    if (n == 0){
        new_node->next = l->head;
        l->head->prev = new_node;
        l->head = new_node;
        return;
    } 

    node* node_ptr = l->head;
    int counter = 0;
    while(node_ptr){
        if (counter == n){
            node_ptr->prev->next = new_node;
            new_node->next = node_ptr;
            node_ptr->prev = new_node;
            return;
        }
        counter++;
        node_ptr = node_ptr->next;
    }


}

void pop_back(llist* l){
    l->tail = l->tail->prev;
    l->tail->next = NULL;
}

void* at(llist* l, int index){
    int n = 0;
    node* currNode = l->head;
    while (n != index && currNode){ // stop loop if index reached or currNode is NULL
        n++;
        currNode = currNode->next;
    }

    if (!currNode) // if exited because out of bounds
        return NULL;

    return currNode->data;
}

void* back(llist* l){
    if (!l->tail) return NULL; // if empty
    return l->tail->data;
}

void free_nodes(llist* l){
    node* currNode = l->tail;
    while (currNode){
        node* prevNode = currNode->prev;
        currNode->data = NULL;
        free(currNode);
        currNode = prevNode;
    }

    l->head = NULL;
    l->tail = NULL;
}

void free_data(llist* l){
    node* currNode = l->tail;
    while (currNode){
        node* prevNode = currNode->prev;
        free(currNode->data);
        currNode->data = NULL;
        free(currNode);
        currNode = prevNode;
    }

    l->head = NULL;
    l->tail = NULL;
}

bool is_empty(llist* l){
    if (l->head)
        return false;
    return true;
}

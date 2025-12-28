#include "day.h"

day* create_day(int n){
    day* d = malloc(sizeof(*d));
    d->day_id = n;
    d->tasks = create_llist();
    return d;
}

task* create_task(char* n, char* desc){
    task* t = malloc(sizeof(*t));
    t->name = n;
    t->description = desc;
    return t;
}

void print(llist* l){
    node* n = l->head;
    while(n != NULL){
        day* d = n->data;
        printf("%d\n", d->day_id);
        print_tasks(d);
        n = n->next;
    }
}

void print_tasks(day* d){
    node* n = d->tasks.head;
    while(n != NULL){
        task* t = n->data;
        printf("%s\n%s\n", t->name, t->description);
        n = n->next;
    }
}
#include "day.h"

day* create_day(int m, int dy, int y){
    day* d = malloc(sizeof(*d));
    d->dt = create_date(m,dy,y);
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
        printf("%d/%d/%d Epoch: %d\n", d->dt.date_month, d->dt.date_day, d->dt.date_year, d->dt.date_epoch);
        print_tasks(d);
        printf("\n");
        n = n->next;
    }
}

void print_tasks(day* d){
    node* n = d->tasks->head;
    while(n != NULL){
        task* t = n->data;
        printf("%s\n%s\n", t->name, t->description);
        n = n->next;
    }
}
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
        printf("%d/%d/%d Epoch: %d\n", d->dt.m, d->dt.d, d->dt.y, d->dt.epoch);
        print_day(d);
        printf("\n");
        n = n->next;
    }
}

void print_day(day* d){
    node* n = d->tasks->head;
    while(n != NULL){
        task* t = n->data;
        printf("%s\n%s\n", t->name, t->description);
        n = n->next;
    }
}

// add task to date
void add_task(llist* days, date target_date, char* name, char* description){
    node* n = days->head;
    int counter = 1;

    task* t = create_task(name,description);

    while (n){
        day* d = n->data;
        // if day already exists in linked list
        if (d->dt.epoch == target_date.epoch){
            push_back(d->tasks, t);
            return;
        }
        // if there is a node afterwards
        if (n->next){
            day* next_day = n->next->data;
            // if between the two days
            if (target_date.epoch > d->dt.epoch && target_date.epoch < next_day->dt.epoch){
                // create new day
                printf("Creating a new day...\n");
                day* new_day = create_day(target_date.m, target_date.d, target_date.y);
                insert(days, counter, new_day);
                push_back(new_day->tasks, t);
                return;
            }
        }
        counter++;
        n = n->next;
    }

    // if day doesn't exist in list and isn't between two other days
    day* new_day = create_day(target_date.m, target_date.d, target_date.y);
    push_back(new_day->tasks, t);
    push_back(days, new_day);
    
}

// display tasks on a certain date
void display_date(llist* days, date dt){
    printf("Looking for tasks on %s\n", dt.string);
    node* n = days->head;
    while(n){
        day* d = n->data;
        if (d->dt.epoch == dt.epoch){
            print_day(d);
            return;
        }
        n = n->next;
    }
    printf("No tasks on that day\n");
}

void display_date_range(llist* days, daterange dtr){
    node* n = days->head;
    while(n){
        day* d = n->data;
        if (d->dt.epoch >= dtr.start && d->dt.epoch <= dtr.end){
            print_day(d);
        }
        n = n->next;
    }
}
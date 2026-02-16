#pragma once
#include <stdio.h>
#include <stdlib.h>
#include "llist.h"
#include "timeconv.h"

typedef struct {
    date dt;
    llist* tasks;
} day;

typedef struct {
    char* name;
    char* description;
} task;

day* create_day(int m, int d, int y);
task* create_task(char* n, char* desc);

// traverse list and print it
void print(llist* l);
void print_day(day* d);

void display_date(llist* days, date dt);
void add_task(llist* days, date dt, char* name, char* description);
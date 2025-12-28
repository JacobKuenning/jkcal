#pragma once
#include <stdio.h>
#include <stdlib.h>
#include "llist.h"


typedef struct {
    int day_id;
    llist tasks;
} day;

typedef struct {
    char* name;
    char* description;
} task;

day* create_day(int n);
task* create_task(char* n, char* desc);

// traverse list and print it
void print(llist* l);
void print_tasks(day* d);
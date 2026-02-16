#pragma once
#include <time.h>
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include "textutils.h"
#include "llist.h"

typedef struct {
    int m;
    int d;
    int y;
    int epoch;
    int wd;
    char string[11]; 
} date;

typedef enum {
    JANUARY,
    FEBRUARY,
    MARCH,
    APRIL,
    MAY,
    JUNE,
    JULY,
    AUGUST,
    SEPTEMBER,
    OCTOBER,
    NOVEMBER,
    DECEMBER
} month;

int string_to_month(char* str);
int string_to_weekday(char *str);
date string_to_date(char* str);
date create_date(int m, int d, int y);
int date_to_epoch_date(date dt);
date epoch_date_to_date(int ed);
int date_to_weekday(date dt);

// returns the days since epoch of the current date according to the system
// this doesn't use seconds, minutes, or hours for day accuracy
int epoch_date_today();
date todays_date();
int todays_weekday();
date next_weekday(int wd, int weeks);
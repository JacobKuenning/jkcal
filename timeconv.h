#pragma once
#include <time.h>
#include <stdio.h>
#include <string.h>
#include <stdlib.h>

typedef struct {
    int date_month;
    int date_day;
    int date_year;
    int date_epoch;
    char date_string[11]; 
} date;

typedef enum{
    SUNDAY,
    MONDAY,
    TUESDAY,
    WEDNESDAY,
    THURSDAY,
    FRIDAY,
    SATURDAY
} weekDay;


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

char* weekday_to_string(weekDay day);
char* month_to_string(month m);
date string_to_date(char* str);
date create_date(int m, int d, int y);
int date_to_epoch_date(date dt);
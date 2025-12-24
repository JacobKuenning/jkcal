#pragma once
#include <ncursesw/ncurses.h>
#include <stdlib.h>
#include "llist.h"

typedef struct{
    WINDOW* frame;
    WINDOW* content;
    bool cursor_over;
} day;

day* create_day(int h, int w, int y, int x, const char *title);
void change_title(day* w, const char* title);
void redraw_day(day* w);
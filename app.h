#pragma once
#include <ncursesw/ncurses.h>
#include "day.h"

typedef struct {
    day* visible_days[7][4];
    int curX;
    int curY; 
} app;

app create_app(void);
void draw_month(app* a);
void manage_input(app* a);
void move_cursor(app* a, int x, int y);

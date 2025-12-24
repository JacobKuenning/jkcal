#include "app.h"

app create_app(void){
    app newApp;
    newApp.curX = 0;
    newApp.curY = 0;
    return newApp;
}

void draw_month(app* a){
    for (int x = 0; x < 7; x++)
    {
        for (int y = 0; y < 4; y++)
        {
            day* new_day = create_day(10,15,y*10,x*15, "Day");
            a->visible_days[x][y] = new_day;   
        }
    }
    
}

void manage_input(app* a){
    bool running = true;
    while (running){
        char c = getchar();
        switch (c){
        case 'q':
            running = false;
            break;
        
        case 'h':
            move_cursor(a, -1, 0);
            break;
        case 'l':
            move_cursor(a, 1, 0);        
            break;
        case 'j':
            move_cursor(a, 0, -1);
            break;
        case 'k':
            move_cursor(a, 0, 1);
            break;
        }
    }
}

void move_cursor(app* a, int x, int y){
    if (a->curX + x < 0 || a->curX + x > 6) return;
    if (a->curY + y < 0 || a->curY + y > 3) return;
    day* old = a->visible_days[a->curX][a->curY];
    old->cursor_over = false;
    redraw_day(old);
    a->curX += x;
    a->curY += y;
    day* new = a->visible_days[a->curX][a->curY];
    new->cursor_over = true;
    redraw_day(new);
}
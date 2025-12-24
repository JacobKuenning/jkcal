#include <ncursesw/ncurses.h>
#include <stdio.h>
#include <time.h>
#include <string.h>
#include "app.h"
#include "llist.h"


int main(){
    initscr();
    curs_set(0); // hide cursor
    
    app main_app = create_app();
    draw_month(&main_app);
    manage_input(&main_app);

    
    endwin();
}


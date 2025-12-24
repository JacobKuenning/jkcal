#include "day.h"


day* create_day(int h, int w, int y, int x, const char *title) {
    day* win = malloc(sizeof(*win));
    win->cursor_over = false;
    win->frame = newwin(h, w, y, x);
    win->content = newwin(h-2, w-2, y+1, x+1);
    refresh();
    change_title(win, title);

    wprintw(win->content, "[ ]");
    wrefresh(win->content);
    return win;
}

void change_title(day* w, const char* title){
    werase(w->frame);
    box(w->frame, 0, 0);
    wprintw(w->frame, "%s", title);
    wrefresh(w->frame);
}

void redraw_day(day* w){
    werase(w->content);
    if (w->cursor_over)
        wprintw(w->content, "[X]");
    else    
        wprintw(w->content, "[ ]");
    wrefresh(w->content);
}

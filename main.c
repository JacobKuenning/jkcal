#include <ncursesw/ncurses.h>
#include <stdio.h>
#include <time.h>
#include <string.h>
#include "app.h"
#include "llist.h"

int main(){
    //initscr();
    llist l = create_llist();

    for (int i = 0; i < 10; i++)
    {
        int* c = malloc(sizeof(int));
        *c = i*10;
        push_back(&l, c);
    }

    printf("%d\n", *(int*)back(&l));
    
    free_data(&l);
    //endwin();
}
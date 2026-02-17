#include <cjson/cJSON.h>
#include <stdio.h>
#include <time.h>
#include <string.h>
#include <stdbool.h>
#include "llist.h"
#include "readfile.h"
#include "timeconv.h"
#include "day.h"
#include "textutils.h"

void debug_arguments(llist* raw_text, llist* flags, llist* keyed_arguments){
    printf("raw text:\n");
    node* n = raw_text->head;
    while(n){
        char* str = n->data;
        printf("%s\n", str);
        n = n->next;
    }

    printf("flags:\n");
    n = flags->head;
    while(n){
        char* str = n->data;
        printf("%s\n", str);
        n = n->next;
    }

    printf("keyed args:\n");
    n = keyed_arguments->head;
    while(n){
        key_value_pair* kvp = n->data;
        printf("%s, %s\n", kvp->key, kvp->value);
        n = n->next;
    }
}

int main(int argc, char** argv){ 
    llist* raw_text = create_llist();
    llist* flags = create_llist();
    llist* keyed_arguments = create_llist();

    // populating argument linked lists
    for (int i = 1; i < argc; i++){
        if (argv[i][0] == '-'){
            char* equals_pos = strstr(argv[i], "=");
            if (equals_pos){ // if there is an '=' character in string
                key_value_pair kvp = create_key_value_pair(argv[i]);
                push_back(keyed_arguments, &kvp);
            } else push_back(flags, argv[i]);
        } else push_back(raw_text, argv[i]);
    }

    char name[256] = {0};
    char description[256] = {0};
    int raw_text_size = size(raw_text);
    if (raw_text_size == 1)
        strcpy(name, at(raw_text, 0));

    if (raw_text_size > 2)
        strcpy(description, at(raw_text,1));

    llist* master = json_to_llist("tasks.json");

    // find days since epoch of local time day
    int days_since_epoch = epoch_date_today();

    //debug_arguments(raw_text, flags, keyed_arguments);
    // process commands and manipulate linked list
    node* n = keyed_arguments->head;
    while(n){
        key_value_pair* kvp = n->data;
        // if key is dt
        if (!strcmp(kvp->key, "-dt")){
            date dt = string_to_date(kvp->value);

            if (!is_empty(raw_text))
                add_task(master, dt, name, description);
            else
                display_date(master, string_to_date(kvp->value));
        }

        else if (!strcmp(kvp->key, "-dtr")){
            daterange dtr = string_to_daterange(kvp->value);
            display_date_range(master, dtr);
        }
        n = n->next;
    }    


    // sort linked list as we add to it using the days since epoch

    llist_to_json(master, "tasks.json");
}


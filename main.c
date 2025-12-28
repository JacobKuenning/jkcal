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

    llist* master = json_to_llist("tasks.json");
}


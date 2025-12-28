#include "textutils.h"

key_value_pair create_key_value_pair(char* literal){
    key_value_pair kvp;
    char str[256];
    strcpy(str, literal);
    
    char* token = strtok(str, "=");
    kvp.key = strdup(token); // dynamically allocated
    token = strtok(NULL, "=");
    kvp.value = strdup(token);

    return kvp;
}
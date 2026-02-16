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

int count_char(char* str, char c){
    int num = 0;
    int i = 0;
    
    while (str[i]){
        if (i == c) num ++;
        i++;
    }
    return num;
}

bool is_unsigned_int(char* str){
    if (*str == '\0')
        return false;

    int index = 0;
    
    while (str[index]){
        if (str[index] < '0' || str[index] > '9')
            return false;
        index ++;
    }
    return true;
}

void str_to_lower(char *s) {
    while (*s) {
        *s = (char)tolower((unsigned char)*s);
        s++;
    }
}
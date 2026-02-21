#pragma once
#include <string.h>
#include <stdbool.h>
#include <ctype.h>
#include "llist.h"

typedef struct{
    char* key;
    char* value;
} key_value_pair;

key_value_pair create_key_value_pair(char* str);

int count_char(char* str, char c);

bool is_unsigned_int(char* str);

void str_to_lower(char *s);

key_value_pair* contains_kvp(llist* list, char* key);
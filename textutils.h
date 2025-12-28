#pragma once
#include <string.h>

typedef struct{
    char* key;
    char* value;
} key_value_pair;

key_value_pair create_key_value_pair(char* str);
#pragma once
#include <stdio.h>
#include <stdlib.h>
#include <cjson/cJSON.h>
#include "llist.h"
#include "day.h"

char* file_to_string(char* filename);
int file_size(FILE* file);
llist* json_to_llist(char* filename);
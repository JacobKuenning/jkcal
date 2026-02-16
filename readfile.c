#include "readfile.h"

char* file_to_string(char* filename){
    FILE* file = fopen(filename, "r");
    int size = file_size(file);

    char* contents = malloc(sizeof(char) * size + 1);
    fread(contents, sizeof(char), size +1, file);
    return contents;
}

int file_size(FILE* file){
    fseek(file, 0, SEEK_END);
    int size = ftell(file);
    fseek(file,0,0); // move marker back to beginning of file
    return size;
}

llist* json_to_llist(char* filename){
    char* rawFileText = file_to_string(filename);
    cJSON* root = cJSON_Parse(rawFileText);
    cJSON* day_json = NULL;

    llist* days = create_llist();

    // traverse array of days
    cJSON_ArrayForEach(day_json, root){ // for each day in array
        cJSON* month_store = cJSON_GetObjectItemCaseSensitive(day_json, "m");
        cJSON* day_store = cJSON_GetObjectItemCaseSensitive(day_json, "d");
        cJSON* year_store = cJSON_GetObjectItemCaseSensitive(day_json, "y");

        day* d = create_day(month_store->valueint, day_store->valueint, year_store->valueint);
        
        cJSON* task_json = NULL;
        cJSON* tasks_array = cJSON_GetObjectItemCaseSensitive(day_json, "tasks");

        // for each task in day
        cJSON_ArrayForEach(task_json, tasks_array){
            cJSON* task_name_store = cJSON_GetObjectItemCaseSensitive(task_json, "task_name");
            cJSON* task_desc_store = cJSON_GetObjectItemCaseSensitive(task_json, "description");

            char* n = task_name_store->valuestring;
            char* desc = task_desc_store->valuestring;
            
            task* t = create_task(n, desc);
            push_back(d->tasks, t); // add task to day
        }

        push_back(days, d); // add day to days
    }
    return days;
}

void llist_to_json(llist* ll, char* filename){
    cJSON* root = cJSON_CreateArray();

    node* n = ll->head;
    while(n){
        day* d = n->data;
        cJSON* day_obj = cJSON_CreateObject();
        cJSON_AddItemToObject(day_obj, "m", cJSON_CreateNumber(d->dt.m));
        cJSON_AddItemToObject(day_obj, "d", cJSON_CreateNumber(d->dt.d));
        cJSON_AddItemToObject(day_obj, "y", cJSON_CreateNumber(d->dt.y));
        cJSON_AddItemToArray(root, day_obj);

        cJSON* tasks_obj = cJSON_CreateArray();
        cJSON_AddItemToObject(day_obj, "tasks", tasks_obj);
        node* n2 = d->tasks->head;
        while(n2){
            task* t = n2->data;
            cJSON* t_obj = cJSON_CreateObject();
            cJSON_AddItemToObject(t_obj, "task_name", cJSON_CreateString(t->name));
            cJSON_AddItemToObject(t_obj, "description", cJSON_CreateString(t->description));
            cJSON_AddItemToArray(tasks_obj, t_obj);
            n2 = n2->next;
        }

        n = n->next;
    }

    char* json_str = cJSON_Print(root);

    FILE* file = fopen(filename, "w");
    fputs(json_str, file);
    fclose(file);
}  
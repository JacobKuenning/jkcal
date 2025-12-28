#include <cjson/cJSON.h>
#include <stdio.h>
#include <time.h>
#include <string.h>
#include "llist.h"
#include "readfile.h"
#include "timeconv.h"
#include "day.h"

int main(int argc, char** argv){ 
    time_t t = time(NULL);
    struct tm* todays_info = localtime(&t);
    

    // char* weekDayStr = weekDayToString((weekDay)todays_info->tm_wday);
    // int day = todays_info->tm_mday;
    // char* monthStr = monthToString((month)todays_info->tm_mon);
    // printf("Today is %s, the %d of %s\n", weekDayStr, day, monthStr);

    char* rawFileText = readFile("tasks.json");
    cJSON* root = cJSON_Parse(rawFileText);
    cJSON* day_json = NULL;

    llist days = create_llist();

    // traverse array of days
    cJSON_ArrayForEach(day_json, root){ // for each day in array
        cJSON* day_id_store = cJSON_GetObjectItemCaseSensitive(day_json, "day_id");
        int day_id = day_id_store->valueint;
        day* d = create_day(day_id);
        
        cJSON* task_json = NULL;
        cJSON* tasks_array = cJSON_GetObjectItemCaseSensitive(day_json, "tasks");

        // for each task in day
        cJSON_ArrayForEach(task_json, tasks_array){
            cJSON* task_name_store = cJSON_GetObjectItemCaseSensitive(task_json, "task_name");
            cJSON* task_desc_store = cJSON_GetObjectItemCaseSensitive(task_json, "description");

            char* n = task_name_store->valuestring;
            char* desc = task_desc_store->valuestring;
            
            task* t = create_task(n, desc);
            push_back(&(d->tasks), t); // add task to day
        }

        push_back(&days, d); // add day to days
    }

    print(&days);
}


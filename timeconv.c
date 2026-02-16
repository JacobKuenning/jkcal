#include "timeconv.h"


int string_to_month(char* str){
    str_to_lower(str);

    if (!str) return -1;

    if (!strcmp(str, "jan") || !strcmp(str, "january")) return 1;
    if (!strcmp(str, "feb") || !strcmp(str, "february")) return 2;
    if (!strcmp(str, "mar") || !strcmp(str, "march")) return 3;
    if (!strcmp(str, "apr") || !strcmp(str, "april")) return 4;
    if (!strcmp(str, "may")) return 5;
    if (!strcmp(str, "jun") || !strcmp(str, "june")) return 6;
    if (!strcmp(str, "jul") || !strcmp(str, "july")) return 7;
    if (!strcmp(str, "aug") || !strcmp(str, "august")) return 8;
    if (!strcmp(str, "sep") || !strcmp(str, "september")) return 9;
    if (!strcmp(str, "oct") || !strcmp(str, "october")) return 10;
    if (!strcmp(str, "nov") || !strcmp(str, "november")) return 11;
    if (!strcmp(str, "dec") || !strcmp(str, "december")) return 12;

    return -1;
}

int string_to_weekday(char *str) {
    if (!str) return -1;

    str_to_lower(str);  // convert to lowercase

    if (!strcmp(str, "sun") || !strcmp(str, "sunday")) return 0;
    if (!strcmp(str, "mon") || !strcmp(str, "monday")) return 1;
    if (!strcmp(str, "tue") || !strcmp(str, "tuesday")) return 2;
    if (!strcmp(str, "wed") || !strcmp(str, "wednesday")) return 3;
    if (!strcmp(str, "thu") || !strcmp(str, "thursday")) return 4;
    if (!strcmp(str, "fri") || !strcmp(str, "friday")) return 5;
    if (!strcmp(str, "sat") || !strcmp(str, "saturday")) return 6;

    return -1;  // invalid input
}

date create_date(int m, int d, int y){
    date dt;
    dt.m = m;
    dt.d = d;
    dt.y = y;

    dt.epoch = date_to_epoch_date(dt);
    dt.wd = date_to_weekday(dt);
    sprintf(dt.string, "%d/%d/%d", m, d, y);

    return dt;
}

date string_to_date(char* literal){
    llist* args = create_llist();
    char str[256]; //buffer
    strcpy(str, literal); // populate array

    int index = 0;
    int token_count = 0;

    // split by '/' and populate integer array
    char* token = strtok(str, "/");
    while (token != NULL){
        push_back(args, token);
        token = strtok(NULL, "/");
        index++;      
        token_count++;  
    }

    date dt;
    date today = todays_date();

    if (token_count == 0 || token_count > 3){
        printf("Invalid date\n");
    }
    else if (token_count == 1){
        char* arg1 = at(args,0);
        int day;
        if (is_unsigned_int(arg1)){
            day = atoi(arg1);
            dt = create_date(today.m, day, today.y);
        } else {
            dt = next_weekday(string_to_weekday(arg1), 1);
        }
    }
    else if (token_count == 2){
        char* arg1 = at(args,0); char* arg2 = at(args,1);
        int month, day;
        if (is_unsigned_int(arg1))
            month = atoi(arg1);
        else
            month = string_to_month(arg1);

        day = atoi(arg2);
        dt = create_date(month, day, today.y);
    }
    else if (token_count == 3){
        char* arg1 = at(args,0); char* arg2 = at(args,1); char* arg3 = at(args,2);
        int month, day, year;
        if (is_unsigned_int(arg1))
            month = atoi(arg1);
        else
            month = string_to_month(arg1);

        day = atoi(arg2);

        if (strlen(arg3) == 2)
            year = 2000 + atoi(arg3);
        else
            year = atoi(arg3);
        
        dt = create_date(month, day, year);
    }

    return dt;
}

int date_to_epoch_date(date dt){
    struct tm t = {0};
    t.tm_year = dt.y - 1900;
    t.tm_mon  = dt.m - 1;
    t.tm_mday = dt.d;
    t.tm_hour = 0;
    t.tm_min  = 0;
    t.tm_sec  = 0;

    time_t seconds = timegm(&t);
    return seconds / 86400;
}

date epoch_date_to_date(int ed){
    time_t seconds_since_epoch = 86400 * ed;
    struct tm t = *gmtime(&seconds_since_epoch);
    return create_date(t.tm_mon + 1, t.tm_mday, t.tm_year + 1900);
}

int date_to_weekday(date dt){
    struct tm t;
    memset(&t, 0, sizeof(t));
    t.tm_year = dt.y - 1900;
    t.tm_mon = dt.m - 1;
    t.tm_mday = dt.d;

    mktime(&t);
    return t.tm_wday;
}

int epoch_date_today(){
    time_t t = time(NULL); // seconds since epoch 
    struct tm today = *localtime(&t); // find today
    today.tm_hour = 0; // zero out data so we are accurate
    today.tm_min = 0;
    today.tm_sec = 0;
    time_t seconds = timegm(&today); // seconds since epoch of beginning of date
    return seconds / 86400;
}

date todays_date(){
    time_t t = time(NULL); // seconds since epoch 
    struct tm today = *localtime(&t); // find today
    date dt = create_date(today.tm_mon + 1, today.tm_mday, 1900 + today.tm_year);
    return dt;
}

int todays_weekday(){
    time_t t = time(NULL); // seconds since epoch 
    struct tm today = *localtime(&t); // find today
    return today.tm_wday;
}

date next_weekday(int wd, int weeks){
    int ed_today = epoch_date_today();
    int weekday_today = todays_weekday();

    int target_ed = ed_today;
    int index = weekday_today;
    while (index != wd){
        index = (index + 1) % (7 * weeks);
        target_ed++;
    }
    return epoch_date_to_date(target_ed);
}
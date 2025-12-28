#include "timeconv.h"

char* weekday_to_string(weekDay day){
    switch (day){
    case SUNDAY:
        return "Sunday";
    case MONDAY:
        return "Monday";
    case TUESDAY:
        return "Tuesday";
    case WEDNESDAY:
        return "Wednesday";
    case THURSDAY:
        return "Thursday";
    case FRIDAY:
        return "Friday";
    case SATURDAY:
        return "Saturday";  
    }
}

char* month_to_string(month m) {
    switch (m) {
        case JANUARY:   
            return "January";
        case FEBRUARY:  
            return "February";
        case MARCH:     
            return "March";
        case APRIL:     
            return "April";
        case MAY:       
            return "May";
        case JUNE:      
            return "June";
        case JULY:      
            return "July";
        case AUGUST:    
            return "August";
        case SEPTEMBER: 
            return "September";
        case OCTOBER:   
            return "October";
        case NOVEMBER:  
            return "November";
        case DECEMBER:  
            return "December";
        default:        
            return "Unknown";
    }
}

date create_date(int m, int d, int y){
    date dt;
    dt.date_month = m;
    dt.date_day = d;
    dt.date_year = y;

    dt.date_epoch = date_to_epoch_date(dt);

    return dt;
}

date string_to_date(char* literal){
    char str[10];
    strcpy(str, literal);

    int array[3];
    int index = 0;

    char* token = strtok(str, "/");
    while (token != NULL){
        array[index] = atoi(token);
        token = strtok(NULL, "/");
        index++;        
    }

    date d = create_date(array[0], array[1], array[2]);
    return d;
}

int date_to_epoch_date(date dt){
    struct tm t = {0};
    t.tm_year = dt.date_year - 1900;
    t.tm_mon  = dt.date_month - 1;
    t.tm_mday = dt.date_day;
    t.tm_hour = 0;
    t.tm_min  = 0;
    t.tm_sec  = 0;

    time_t seconds = timegm(&t);
    return seconds / 86400;
}
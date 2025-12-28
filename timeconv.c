#include "timeconv.h"

char* weekDayToString(weekDay day){
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

char* monthToString(month m) {
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
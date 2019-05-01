#ifndef COMPONENT_H
#define COMPONENT_H

typedef struct{
    char date[11];  // 1st Column: Date (YYYY-MM-DD)
    double amount;  // 2nd Column: [+/-] Amount (Initial Balance for 1st Row)
    char cat[4];    // 3rd Column: Catagory (Currencyfor 1st Row)
    char note[101]; // 4th Column: Note
}DATA;

typedef struct{
    char code[4];   // Catagory Code
    char name[20];  // Catagory Name
}CAT;

typedef struct{
    int count;
    int start_line;
    int max_line;
}EDIT;

typedef struct{
    char code[4];
    char name[20];
    double amount;
}STAT;

/* Current date */
void current_date(char *date){
    time_t t = time(NULL);
    struct tm timeinfo = *localtime(&t);
    sprintf(date, "%04d-%02d-%02d", timeinfo.tm_year+1900, timeinfo.tm_mon+1, timeinfo.tm_mday);
}

/* Check the date is valid or not */
int valid_date(char *str){
    char date[11];
    strcpy(date, str);
    char *token = strtok(date, "-");
    int year = atoi(token);
    token = strtok(NULL, "-");
    int month = atoi(token);
    token = strtok(NULL, "\0");
    int day = atoi(token);
    struct tm timeinfo = {0};
    timeinfo.tm_year = year-1900;
    timeinfo.tm_mon = month-1;
    timeinfo.tm_mday = day;
    timeinfo.tm_isdst = -1;
    time_t r = mktime(&timeinfo);
    if(r == -1 || (day != timeinfo.tm_mday) || (month-1 != timeinfo.tm_mon) || (year-1900 != timeinfo.tm_year))
        return 0;
    return 1;
}

#endif

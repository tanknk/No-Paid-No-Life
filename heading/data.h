#ifndef DATA_H
#define DATA_H

/* Convert string to DATA */
DATA stodata(char* str){
    DATA data;
    char *token = strtok(str, ",");
    for(int i = 0; i < 4; i++){
        switch(i){
            case 0: strcpy(data.date, token); break;
            case 1: data.amount = atof(token); break;
            case 2: strcpy(data.cat, token); break;
            case 3: strcpy(data.note, token); break;
        }
        if(i < 2)
            token = strtok(NULL, ",");
        else
            token = strtok(NULL, "\n");
    }
    return data;
}

/* Convert DATA to string */
void datatos(char* str, DATA data){
    strcpy(str, data.date);
    char amount[30];
    sprintf(amount, "%.3f", data.amount);
    strcat(str, ","); strcat(str, amount);
    strcat(str, ","); strcat(str, data.cat);
    strcat(str, ","); strcat(str, data.note);
}

/* Select currency (USD/THB) */
int select_currency(char* str){
    printf("\n1: USD/US Dollar\n");
    printf("2: THB/TH Baht\n");
    printf("Choose currency: ");
    char choice;
    scanf(" %c", &choice);
    switch(choice){
        case '1':
            strcpy(str, "USD");
            return 0;
        case '2':
            strcpy(str, "THB");
            return 0;
        default:
            return 1;
    }

}

/* Enter initial balance */
int enter_balance(double* double_ptr){
    printf("\nEnter initial balance: ");
    scanf(" %lf", double_ptr);
    if(*double_ptr >= 0)
        return 0;
    return 1;
}

/* Initialize wallet */
DATA init_wallet(){
    DATA data;
    time_t t = time(NULL);
    struct tm timeinfo = *localtime(&t);
    sprintf(data.date, "%04d-%02d-%02d", timeinfo.tm_year+1900, timeinfo.tm_mon+1, timeinfo.tm_mday);
    while(select_currency(data.cat))
        printf("Error, Please thy again.\n"); 
    while(enter_balance(&data.amount))
        printf("Error, Please thy again.\n");
    strcpy(data.note, "-\n");
    return data;
}

#endif

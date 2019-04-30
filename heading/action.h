#ifndef ACTION_H
#define ACTION_H

#define DATA_LINE 200

/* Swap string */
void swap(char *str1, char *str2) { 
    char *temp = str1; 
    str1 = str2;
    str2 = temp;
}

/* Counting line of file */
int count_line(char* filename){
    FILE *fp = fopen(filename, "r");
    int count = 0;
    char str[DATA_LINE];
    while(fgets(str, DATA_LINE, fp) != NULL)
        count++;
    return count;
}

/* Sorting transection */
int sort_trans(char* filename){
    FILE *fp_1 = fopen(filename, "r");
    int count = count_line(filename)-1;
    // No transection
    if(count == 0)
        return 0;
    char start[DATA_LINE];
    fgets(start, DATA_LINE, fp_1);
    char str[count][DATA_LINE];
    for(int i = 0; i < count; i++)
        fgets(str[i], DATA_LINE, fp_1);
    for(int i = 1; i < count; i++){
        int j = i-1;
        char temp[DATA_LINE];
        strcpy(temp, str[i]);
        while(j >= 0 && strncmp(temp, str[j], 10) < 0){
            strcpy(str[j+1], str[j]);
            j = j-1;
        }
        strcpy(str[j+1], temp);
    }
    fclose(fp_1);
    FILE *fp_2 = fopen(filename, "w");
    fprintf(fp_2, "%s", start);
    for(int i = 0; i < count; i++)
        fprintf(fp_2, "%s", str[i]);
    fclose(fp_2);
    return 0;
}

/* View current transections */
void view_trans(char* filename){
    char date[8];
    printf("Enter date [YYYY-MM]: ");
    scanf(" %s", date);
    printf("%s\n", date);
    FILE *fp = fopen(filename, "r");
    DATA data;
    CAT cat;
    CAT subcat;
    char code[4];
    char str[DATA_LINE];
    char day[4] = "-00";
    char date_full[11];
    fgets(str, DATA_LINE, fp);
    while(fgets(str, DATA_LINE, fp) != NULL){
        if(strncmp(date, str, 7) < 0){
            printf("No transection.\n");
            break;
        }else if(strncmp(date, str, 7) == 0){
            data = stodata(str);
            strcpy(code, data.cat);
            code[2] = '0';
            cat = codetocat(code);
            subcat = codetocat(data.cat);
            if(strcmp(day, data.date+7) != 0){
                strcpy(date_full, date);
                sprintf(day, "%s", data.date+7);
                strcat(date_full, day);
                printf("Day %s\n", day+1);
            }
            printf("%+12.3lf\t", data.amount*(data.cat[0] == 'E'?-1:1));
            if(strcmp(data.cat, code) != 0)
                printf("%s: %s\n", cat.name, subcat.name);
            else
                printf("%s\n", subcat.name);
            printf("Note: %s\n", data.note);
        }else
            continue;
    }
    fclose(fp);
}

/* Add a new transection */
void add_trans(char* filename){
    DATA trans_data;
    char cat[4];
    select_cat(cat);
    strcpy(trans_data.cat, cat);
    printf("Enter amount: ");
    scanf(" %lf", &trans_data.amount);
    printf("Enter note: ");
    scanf(" %[^\n]", trans_data.note);
    printf("Enter date [YYYY-MM-DD]: ");
    scanf(" %s", trans_data.date);
    FILE* fp = fopen(filename, "ab+");
    char str[DATA_LINE];
    datatos(str, trans_data);
    strcat(str, "\n");
    fprintf(fp, str);
    fclose(fp);
}

/* Edit a transection */
void edit_trans(char* filename){
    view_trans(filename);
}

void view_report(char* filename){
    
}

int take_action(char* filename){
    sort_trans(filename);
    // Overview
    double inflow = 0, outflow = 0;
    FILE* fp = fopen(filename, "r");
    char str[DATA_LINE];
    char currency[4];
    while(fgets(str, DATA_LINE, fp) != NULL){
        DATA trans = stodata(str);
        // Currency
        if(trans.cat[0] != 'I' && trans.cat[0] != 'E' )
            strcpy(currency, trans.cat); 
        // Add to Outflow if Catagory is Expense
        if(trans.cat[0] == 'E')
            outflow += trans.amount;
        else
            inflow += trans.amount;
    }
    fclose(fp);
    printf("\nInflow: \t%.3f %s\n", inflow, currency);
    printf("Outflow: \t%.3f %s\n", outflow, currency);
    printf("Net Balance: \t%.3f %s\n", inflow-outflow, currency);
    // Take action
    printf("\n1: View Transections\n");
    printf("2: Add Transection\n");
    printf("3: Edit Transection\n");
    printf("4: View Report\n");
    printf("5: Exit\n");
    printf("Choose action: ");
    char choice;
    scanf(" %c", &choice);
    switch(choice){
        case '1':
            view_trans(filename); break;
        case '2':
            add_trans(filename); break;
        case '3':
            edit_trans(filename); break;
        case '4':
            view_report(filename); break;
        case '5':
            return 0;
        default:
            printf("Error, Please thy again.\n");
    }
    return 1;
}

#endif

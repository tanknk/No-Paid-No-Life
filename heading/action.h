#ifndef ACTION_H
#define ACTION_H

#define DATA_LINE 200

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
EDIT view_trans(char* filename){
    EDIT edit;
    edit.count = 0;
    edit.start_line = 0;
    edit.max_line = 1;
    char date[11];
    jump1:
    printf("\n1: Current month\n");
    printf("2: Specific month\n");
    printf("Choose action: ");
    char choice;
    scanf(" %c", &choice);
    switch(choice){
        case '1':
            current_date(date);
            goto jump3;
        case '2':
            goto jump2;
        default:
            printf("Error, Please try again.\n");
            goto jump1;
    }
    jump2:
    printf("\nEnter date [YYYY-MM]: ");
    scanf(" %s", date);
    // Check is date valid or not
    strcat(date, "-01");
    if(!valid_date(date)){
        printf("Error, Invalid date.\n");
        goto jump2;
    }
    jump3:
    printf("\n%.7s\n", date);
    FILE *fp = fopen(filename, "r");
    DATA data;
    CAT cat;
    CAT subcat;
    char code[4];
    char str[DATA_LINE];
    fgets(str, DATA_LINE, fp);
    while(fgets(str, DATA_LINE, fp) != NULL){
        edit.max_line++;
        if(strncmp(date, str, 7) > 0){
            edit.start_line++;              // Line count
        }else if(strncmp(date, str, 7) == 0){
            edit.count++;                   // Counter count
            data = stodata(str);
            strcpy(code, data.cat);
            code[2] = '0';
            cat = codetocat(code);
            subcat = codetocat(data.cat);
            printf("%03d: [%s]", edit.count, data.date);
            printf("%+12.3lf| ", data.amount*(data.cat[0] == 'E'?-1:1));
            if(strcmp(data.cat, code) != 0)
                printf("%s: %s", cat.name, subcat.name);
            else
                printf("%s", subcat.name);
            printf("\n\tNOTE: %s\n", data.note);
        }
    }
    if(edit.count == 0)
        printf("No transection\n");
    fclose(fp);
    return edit;
}

/* Add a new transection */
void add_trans(char* filename){
    DATA trans_data;
    char cat[4];
    select_cat(cat);
    strcpy(trans_data.cat, cat);
    while(enter_amount(&trans_data.amount))
        printf("Error, Please try again.\n");
    printf("Enter note: ");
    scanf(" %[^\n]", trans_data.note);
    while(1){
        printf("Enter date [YYYY-MM-DD]: ");
        scanf(" %s", trans_data.date);
        if(valid_date(trans_data.date)){
            break;
        }
        printf("Error, Invalid date.\n");
    }
    FILE* fp = fopen(filename, "ab+");
    char str[DATA_LINE];
    datatos(str, trans_data);
    strcat(str, "\n");
    fprintf(fp, str);
    fclose(fp);
}

/* Edit a transection */
int edit_trans(char* filename){
    EDIT edit = view_trans(filename);
    if(edit.count == 0)
        return 0;
    jump1:
    printf("\nChoose line: ");
    int choice;
    scanf(" %d", &choice);
    if(choice <= 0 || choice > edit.count){
        printf("Error, Please try again.\n");
        goto jump1;
    }
    // Backup file
    DATA data_ls[edit.max_line];
    data_list(filename, data_ls);
    // Display Data
    CAT cat;
    CAT subcat;
    int select_int = edit.start_line+choice;
    char date[11];
    char code[4];
    char act_choice;
    jump2:
    strcpy(code, data_ls[select_int].cat);
    code[2] = '0';
    cat = codetocat(code);
    subcat = codetocat(data_ls[select_int].cat);
    printf("\n1: Date: %s\n", data_ls[select_int].date);
    printf("2: Amount: %.3lf\n", data_ls[select_int].amount);
    printf("3: Catagory: ", data_ls[select_int].cat);
    if(strcmp(data_ls[select_int].cat, code) != 0)
        printf("%s: %s\n", cat.name, subcat.name);
    else
        printf("%s\n", subcat.name);
    printf("4: Note: %s\n", data_ls[select_int].note);
    printf("0: Save edit\n");
    printf("Choose action/line to edit: ");
    scanf(" %c", &act_choice);
    switch(act_choice){
        case '0':
            break;
        case '1':
            while(1){
                printf("\nEnter date [YYYY-MM-DD]: ");
                scanf(" %s", date);
                if(valid_date(date)){
                    strcpy(data_ls[select_int].date, date);
                    break;
                }
                printf("Error, Invalid date.\n");
            }
            goto jump2;            
        case '2':
            while(enter_amount(&data_ls[select_int].amount))
                printf("Error, Please try again.\n");
            goto jump2;
        case '3':
            select_cat(data_ls[select_int].cat);
            goto jump2;
        case '4':
            printf("\nEnter note: ");
            scanf(" %[^\n]", data_ls[select_int].note);
        default:
            printf("Error, Please try again.\n");
            goto jump2;
    }
    // Write file
    FILE *fp = fopen(filename, "w");
    char str[DATA_LINE];
    for(int i = 0; i < edit.max_line; i++){
        datatos(str, data_ls[i]);
        fprintf(fp, "%s\n", str);
    }
    fclose(fp);
    return 0;
}

/* View report */
void view_report(char* filename){
    
}

int take_action(char* filename){
    sort_trans(filename);
    // Overview
    double inflow = 0, outflow = 0;
    FILE *fp = fopen(filename, "r");
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
            printf("Error, Please try again.\n");
    }
    return 1;
}

#endif
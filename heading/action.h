#ifndef ACTION_H
#define ACTION_H

#define DATA_LINE 200

/* Counting line of file */
int count_line(char *filename){
    FILE* fp = fopen(filename, "r");
    int count = 0;
    char str[DATA_LINE];
    while(fgets(str, DATA_LINE, fp) != NULL)
        count++;
    fclose(fp);
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
    trans_data.cat[3] = '\0';
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
    printf("3: Category: ", data_ls[select_int].cat);
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
            goto jump2;
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
void view_report(char* filename, char* currency){
    // monthly/yearly
    char date[11];
    char date_check[11];
    jump:
    printf("\nEnter date [YYYY/YYYY-MM]: ");
    scanf(" %s", date);
    strcpy(date_check, date);
    if(strlen(date) == 4){
        strcat(date_check, "-01-01");
    }else if(strlen(date) == 7){
        strcat(date_check, "-01");
    }
    // check valid date
    if(!valid_date(date_check)){
        printf("Error, Invalid date.\n");
        goto jump;
    }
    // read file
    FILE *fp = fopen(filename, "r");
    int lines = count_line(filename);
    double initial = 0.0;
    // income
    STAT income[7];
    for(int i = 0; i < 7; i++){
        strcpy(income[i].code, "I");
        income[i].code[1] = 48+i;
        income[i].code[2] = '0';
        income[i].code[3] = '\0';
        strcpy(income[i].name, codetocat(income[i].code).name);
        income[i].amount = 0.0;
    }
    // expense
    STAT expense[15];
    for(int i = 0; i < 15; i++){
        strcpy(expense[i].code, "E");
        expense[i].code[1] = i+(i<=9?48:55);
        expense[i].code[2] = '0';
        expense[i].code[3] = '\0';
        strcpy(expense[i].name, codetocat(expense[i].code).name);
        expense[i].amount = 0.0;
    }
    DATA data_ls[lines];
    data_list(filename, data_ls);
    for(int i = 0; i < lines; i++){
        if(strncmp(date, data_ls[i].date, strlen(date)) > 0){
            initial += ((data_ls[i].cat[0] == 'E'?-1:1)*data_ls[i].amount);
        }else if(strncmp(date, data_ls[i].date, strlen(date)) == 0){
            if(data_ls[i].cat[0] == 'E'){
                // expense
                for(int j = 1; j < 15; j++)
                    // same sub-category
                    if(data_ls[i].cat[1] == expense[j].code[1]){
                        expense[j].amount += data_ls[i].amount;
                        expense[0].amount += data_ls[i].amount;
                    }
            }else{
                // income
                for(int j = 1; j < 7; j++)
                    // same sub-category
                    if(data_ls[i].cat[1] == income[j].code[1]){
                        income[j].amount += data_ls[i].amount;
                        income[0].amount += data_ls[i].amount;
                    }
            }
        }
    }
    fclose(fp);
    // overview report
    CAT cat;
    char code[4];
    printf("\n%s Report:\n", date);
    printf("Initial: %.3lf %s\n", initial, currency);
    printf("Income: %.3lf %s\n", income[0].amount, currency);
    printf("Expense: %.3lf %s\n", expense[0].amount, currency);
    printf("Net: %.3lf %s\n", initial+income[0].amount-expense[0].amount, currency);
    // income report
    printf("\nIncome:\n");
    for(int i = 1; i < 7; i++)
        if(income[i].amount > 0){
            printf("[%6.2lf%%] %+12.3lf| %s\n", 100*income[i].amount/income[0].amount, income[i].amount, income[i].name);
        }
    // expense report
    printf("\nExpense:\n");
    for(int i = 1; i < 15; i++)
        if(expense[i].amount > 0){
            printf("[%6.2lf%%] %+12.3lf| %s\n", 100*expense[i].amount/expense[0].amount, expense[i].amount, expense[i].name);
        }
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
        // Add to Outflow if Category is Expense
        if(trans.cat[0] == 'E')
            outflow += trans.amount;
        else
            inflow += trans.amount;
    }
    fclose(fp);
    system("cls"); 
    printf("\n+-------------------------------+\n");
    printf("Overview\n");
    printf("Inflow: \t%.3f %s\n", inflow, currency);
    printf("Outflow: \t%.3f %s\n", outflow, currency);
    printf("Net Balance: \t%.3f %s\n", inflow-outflow, currency);
    printf("+-------------------------------+\n");
    // Take action
    printf("\n+--------------------+\n");
    printf("Choose your action\n");
    printf("1: View Transections\n");
    printf("2: Add Transection\n");
    printf("3: Edit Transection\n");
    printf("4: View Report\n");
    printf("5: Exit\n");
    printf("+--------------------+\n");
    printf("Choose action: ");
    char choice;
    scanf(" %c", &choice);
    switch(choice){
        case '1':
            system("cls"); view_trans(filename); interupt(); break;
        case '2':
            system("cls"); add_trans(filename); interupt(); break;
        case '3':
            system("cls"); edit_trans(filename); interupt(); break;
        case '4':
            system("cls"); view_report(filename, currency); interupt(); break;
        case '5':
            return 0;
        default:
            printf("Error, Please try again.\n");
    }
    return 1;
}

#endif

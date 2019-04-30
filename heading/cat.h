#ifndef CAT_H
#define CAT_H

#define CAT_SIZE 52
#define CAT_LINE 30

/* Convert string to CAT */
CAT stocat(char* str){
    CAT cat;
    char *token = strtok(str, ",");
    strcpy(cat.code, token);
    token = strtok(NULL, "\n");
    strcpy(cat.name, token);
    return cat;
}

/* Read catagory list */
void cat_list(CAT* cat){
    FILE* fp = fopen("./data/cat.csv", "r");
    char str[CAT_LINE];
    fgets(str, CAT_LINE, fp);
    for(int i = 0; i < CAT_SIZE; i++){
        fgets(str, CAT_LINE, fp);
        cat[i] = stocat(str);
    }
    fclose(fp);
}

/* Select catagory */
int select_cat(char* str){
    CAT cat_ls[CAT_SIZE];
    cat_list(cat_ls);
    // 1st Character
    while(1){
        printf("\n1: Income\n");
        printf("2: Expense\n");
        printf("Choose catagory: ");
        char choice;
        scanf(" %c", &choice);
        if(choice == '1'){
            strcpy(str, "I");
            break;
        }else if(choice == '2'){
            strcpy(str, "E");
            break;
        }
        printf("Error, Please thy again.\n");
    }
    // 2nd Character
    while(1){
        printf("\n");
        for(int i = 0; i < CAT_SIZE; i++)
            if(cat_ls[i].code[0] == str[0] && cat_ls[i].code[2] == '0'){
                if(cat_ls[i].code[1] != '0')
                    printf("%c: ", cat_ls[i].code[1]);
                printf("%s\n", cat_ls[i].name);
            }
        printf("Choose catagory: ");
        char choice;
        scanf(" %c", &choice);
        for(int i = 0; i < CAT_SIZE; i++){
            if(cat_ls[i].code[0] == str[0] && cat_ls[i].code[1] == choice && cat_ls[i].code[2] == '0'){
                str[1] = choice;
                goto jump1;
            }
        }
        printf("Error, Please thy again.\n");   
    }
    jump1:
    // Skip 3rd if catagory is Income
    if(str[0] == 'I'){
        str[2] = '0';
        goto jump2;
    }   
    // 3rd Character
    int count;
    while(1){
        count = 0;
        printf("\n");
        for(int i = 0; i < CAT_SIZE; i++)
            if(cat_ls[i].code[0] == str[0] && cat_ls[i].code[1] == str[1]){
                if(cat_ls[i].code[2] != '0'){
                    printf("%c: ", cat_ls[i].code[2]);
                    count++;
                }
                printf("%s\n", cat_ls[i].name);
            }
        if(count == 0)
            goto jump2;
        printf("Choose catagory: ");
        char choice;
        scanf(" %c", &choice);
        for(int i = 0; i < CAT_SIZE; i++){
            if(cat_ls[i].code[0] == str[0] && cat_ls[i].code[1] == str[1] && cat_ls[i].code[2] == choice){
                str[2] = choice;
                goto jump1;
            }
        }
        printf("Error, Please thy again.\n");   
    }
    jump2:
    return 0;
}

/* Convert code to CAT */
CAT codetocat(char* str){
    CAT cat_ls[CAT_SIZE];
    cat_list(cat_ls);
    for(int i = 0; i < CAT_SIZE; i++){
        if(strcmp(str, cat_ls[i].code) == 0)
            return cat_ls[i];
    }
}

#endif

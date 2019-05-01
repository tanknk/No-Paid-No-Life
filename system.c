#include <stdio.h>
#include <stdlib.h>
#include <conio.h>
#include <ctype.h>
#include <string.h>
#include <time.h>
#include "heading/component.h"
#include "heading/data.h"
#include "heading/cat.h"
#include "heading/action.h"

struct save{
    char id[10];
    char pass[10];
}data;

struct idcheck{
    char id_check[10];
}id_data;

int regis();
int intro();
int login();

int main(){
    intro();
}

int regis(){
    char decision;
    char id[10], buffer[10], ch;
    int status_id = 1;
    FILE *check;
    check = fopen("./data/check_id.txt", "rb"); // CHECK ID IN SYSTEM
    system("cls");
    printf("+-----------------------------------------------------------+\n");
    printf("Please Enter Your Information Correctly\n");
    printf("Username and Password length must not more than 10 characters\n");
    printf("+-----------------------------------------------------------+\n");
    int cant = 1, pos =0;
    while(cant){
        cant = 0;
        pos = 0;
        printf("Enter your username: ");
        while(1){
            ch = getch();
            if (ch == 13 && pos == 0){
                
                printf("\n");
                printf("+-----------------+\n");
                printf("No username entered\n");
                printf("1: Try again\n");
                printf("2: Exit\n");
                printf("+-----------------+\n");
                jump2:
                printf("Choose action: ");
                scanf(" %c", &decision);
                switch(decision){
                    case '1': break;
                    case '2': return 0; break;
                    default: printf("Error, Please try again.\n"); goto jump2;
                    }
                cant = 1;
                break;
            }else if (ch == 13){ //ENTER
                break;
            }else if(ch == 8){ //BACKSPACE
                if (pos > 0){ //ถ้าเป็น 0 คือยังไม่ได้กรอกพาส
                    pos--;
                    id[pos] == '\0';
                    printf("\b \b");}
            }
            else if (ch == 32 || ch == 9 || !isalnum(ch)){ //SPACE , TAB , SPECIAL
                continue;}
            else{
                if(pos < 10){
                    id[pos] = ch;
                    pos++;
                    printf("%c", ch);
                }else{
                    continue;
                }
            }}
            id[pos] = '\0';
    }
    printf("\n");
    while(fread(&id_data,sizeof(id_data),1,check) == 1){
        if(strcmp(id, id_data.id_check) == 0){
            status_id = 0;
            break;
        }
    }
    if(status_id){
        strcpy(data.id,id);
        fclose(check);
        strcpy(buffer, "./data/");
        strcat(buffer, data.id);
        strcat(buffer, ".csv");
        strcpy(id_data.id_check, data.id);
        FILE *regis;
        regis = fopen(buffer, "ab+");
        /* PASSWORD */
        cant = 1;
        pos = 0;
        char password[10], ch;
        while(cant){
            cant = 0;
            printf("Enter your password: ");
            while(1){
                ch = getch();
                if (ch == 13 && pos == 0){
                    printf("\n");
                    printf("+-----------------+\n");
                    printf("No password entered\n");
                    printf("1: Try again\n");
                    printf("2: Exit\n");
                    printf("+-----------------+\n");
                    jump3:
                    printf("Choose action: ");
                    scanf(" %c", &decision);
                    switch(decision){
                        case '1': break;
                        case '2': return 0; break;
                        default: printf("Error, Please try again.\n"); goto jump3;
                        }
                    cant = 1;
                    break;
                    }
                else if (ch == 13){ //ENTER
                    break;
                    }
                else if(ch == 8){ //BACKSPACE
                    if (pos > 0){ //ถ้าเป็น 0 คือยังไม่ได้กรอกพาส
                        pos--;
                        password[pos] == '\0';
                        printf("\b \b");}
                    }
                else if (ch == 32 || ch == 9 || !isalnum(ch)){ //SPACE , TAB , SPECIAL
                    continue;
                    }
                else{
                    if(pos < 10){
                        password[pos] = ch;
                        pos++;
                        printf("*");
                        }
                    else{
                        continue;
                        }
                    }   
                }
                password[pos] = '\0';
            }
        printf("\n");
        /* RE-PASSWORD */
        cant = 1, pos = 0;
        char password2[10];
        while(cant){
            cant = 0;
            printf("Enter your re-password: ");
            while(1){
                ch = getch();
                if (ch == 13 && pos == 0){
                    printf("\n");
                    printf("+-----------------+\n");
                    printf("No password entered\n");
                    printf("1: Try again\n");
                    printf("2: Exit\n");
                    printf("+-----------------+\n");
                    jump4:
                    printf("Choose action: ");
                    scanf(" %c", &decision);
                    switch(decision){
                        case '1': break;
                        case '2': return 0; break;
                        default: printf("Error, Please try again.\n"); goto jump4;
                    }
                    cant = 1;
                    break;
                    }
                    else if (ch == 13){ //ENTER
                        break;
                    }
                    else if(ch == 8){ //BACKSPACE
                        if (pos > 0){ //ถ้าเป็น 0 คือยังไม่ได้กรอกพาส
                            pos--;
                            password2[pos] == '\0';
                            printf("\b \b");
                        }
                    }
                    else if (ch == 32 || ch == 9 || !isalnum(ch)){ //SPACE , TAB , SPECIAL
                        continue;
                    }
                    else{
                        if(pos < 10){
                            password2[pos] = ch;
                            pos++;
                            printf("*");
                        }
                        else{
                            continue;
                        }
                    }
                }
                password2[pos] = '\0';
            }
        printf("\n");
        if(strcmp(password, password2) == 0){
            strcpy(data.pass, password);
                printf("+-----------------------+\n");
                printf("Are you sure to register?\n");
                printf("1: Sure\n");
                printf("2: Not sure\n");
                printf("+-----------------------+\n");
                jump5:
                printf("Choose action: ");
                scanf(" %c", &decision);
                switch(decision){
                case '1':
                    system("cls");
                    fwrite(&data, sizeof(data), 1, regis);
                    fclose(regis);
                    FILE *check;
                    check = fopen("./data/check_id.txt", "ab+");
                    fwrite(&id_data, sizeof(id_data), 1, check);
                    fclose(check);
                    printf("+-----------------+\n");
                    printf("Register Successful\n");
                    printf("+-----------------+\n");
                    interrupt();
                case '2':
                    system("cls");
                    intro();
                default: printf("Error, Please try again.\n"); goto jump5;
                }
            }
        else{
            printf("+-------------------------------+\n");
            printf("Register failed\n");
            printf("Password and Re-Password not same\n");
            printf("+-------------------------------+\n");
            interrupt();
        }
    }
    else{
        printf("+-----------------------------+\n");
        printf("Register failed\n");
        printf("This username is already exists\n");
        printf("+-----------------------------+\n");
        interrupt();
    }
}

int intro(){
    system("cls");
    char decision;
    printf("+------------------------+\n");
    printf("WELCOME TO NO PAID NO LIFE\n");
    printf("1: Sign up\n");
    printf("2: Sign in\n");
    printf("3: Exit\n");
    printf("+------------------------+\n");
    jump:
    printf("Choose action: ");
    scanf(" %c", &decision);
    switch(decision){
        case '1': regis(); break;
        case '2': login(); break;
        case '3': return 0; break;
        default: printf("Error, Please try again.\n"); goto jump;
    }
}

int login(){
    system("cls");
    char id[10], idbuff[10], buffer[10], pass[10];
    int status = 0;
    printf("Enter your username: ");
    scanf("%s", id);
    FILE *check;
    check = fopen("./data/check_id.txt", "rb"); // CHECK ID IN SYSTEM
    while(fread(&id_data,sizeof(id_data),1,check) == 1){
        if(strcmp(id, id_data.id_check) == 0){
            status = 1;
            break;
        }
    }
    if(status){
        strcpy(idbuff, id);
        strcpy(buffer, "./data/");
        strcat(buffer, id);
        strcat(buffer, ".csv");
        FILE *logincsv;
        logincsv = fopen(buffer, "ab+");
        int state = 0;
        int cant = 1, pos = 0;
        char ch;
        char decision;
        while(cant){
            cant = 0;
            printf("Enter your password: ");
            while(1){
                ch = getch();
                if (ch == 13 && pos == 0){
                    printf("\n");
                    printf("+-----------------+\n");
                    printf("No password entered\n");
                    printf("1: Try again\n");
                    printf("2: Exit\n");
                    printf("+-----------------+\n");
                    jump6:
                    printf("Choose action: ");
                    scanf(" %c", &decision);
                    switch(decision){
                        case '1': break;
                        case '2': return 0; break;
                        default: printf("Error, Please try again.\n"); goto jump6;
                        }
                    cant = 1;
                    break;
                    }
                else if (ch == 13){ //ENTER
                    break;
                    }
                else if(ch == 8){ //BACKSPACE
                    if (pos > 0){ //ถ้าเป็น 0 คือยังไม่ได้กรอกพาส
                        pos--;
                        pass[pos] == '\0';
                        printf("\b \b");}
                    }
                else if (ch == 32 || ch == 9 || !isalnum(ch)){ //SPACE , TAB , SPECIAL
                    continue;
                    }
                else{
                    if(pos < 10){
                        pass[pos] = ch;
                        pos++;
                        printf("*");
                        }
                    else{
                        continue;
                        }
                    }   
                }
                pass[pos] = '\0';
            }
        printf("\n");
        while(fread(&data,sizeof(data),1,logincsv) == 1){
            if(strcmp(id, data.id) == 0 && strcmp(pass, data.pass) == 0){
                state = 1;
                break;
            }
        }
        if(state){
            fclose(logincsv);
            system("cls");
            // Filename (Maximun line size: 200)
            char filename[30];
            strcpy(filename, "./data/wallet/");
            strcat(filename, id);
            strcat(filename, ".csv");
            // Open file
            FILE *fp = fopen(filename, "ab+");
            // Initialize wallet
            int ch = getc(fp);
            if (feof(fp)){
                DATA init_data = init_wallet();
                char str[200];
                datatos(str, init_data);
                fprintf(fp, str);
            }
            fclose(fp);
            while(take_action(filename)){
                continue;
            }
        }
        else{
            printf("+-----------------------+\n");
            printf("Wrong password, Try again\n");
            printf("+-----------------------+\n");
            interrupt();
        }
    }
    else{
        printf("+---------------------+\n");
        printf("This username not found\n");
        printf("+---------------------+\n");
        interrupt();
    }
}

int interrupt(){
    char ch;
    printf("Press any key to continue..\n");
    ch = getch();
    intro();
}

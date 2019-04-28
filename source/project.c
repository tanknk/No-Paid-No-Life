#include "stdio.h"
#include "string.h"
#include "conio.h"
#include "ctype.h"
#include "stdlib.h"

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
    int decision;
    char buffer[10];
    FILE *check;
    check = fopen("../data/check_id.txt", "rb"); // CHECK ID IN SYSTEM
    system("cls");
    printf("Please Enter Your Information Correctly\n");
    /* USERNAME */
    printf("Username: ");
    scanf("%s", data.id);
    strcpy(buffer, "../data/");
    strcat(buffer, data.id);
    strcat(buffer, ".csv");
    strcpy(id_data.id_check, data.id);
    FILE *regis;
    regis = fopen(buffer, "ab+");
    /* PASSWORD */
    int cant = 1, pos = 0;
    char password[10], ch;
    while(cant){
        cant = 0;
        printf("Your Password : ");
        while(1){
            ch = getch();
            if (ch == 13 && pos == 0){
                printf("\n");
                printf("+------------------------------------------------+\n");
                printf(":               No Password Entered              :\n");
                printf(":          Put 1 if you want to try again        :\n");
                printf(":          Put 2 if you want to shut down        :\n");
                printf("+------------------------------------------------+\n");
                printf("Your Choice : ");
                scanf("%d", &decision);
                while(decision > 2){
                    printf("Wrong command, Try again pls\n");
                    printf("Your Choice : ");
                    scanf("%d", &decision);
                    }
                switch(decision){
                    case 1: break;
                    case 2: return 0; break;
                    }
                cant = 1;
                break;
                }
            else if (ch == 13){ //ENTER
                break;
                }
            else if(ch == 8){ //BACLSPACE
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
        printf("Re-Password : ");
        while(1){
            ch = getch();
            if (ch == 13 && pos == 0){
                printf("\n");
                printf("+------------------------------------------------+\n");
                printf(":               No Password Entered              :\n");
                printf(":          Put 1 if you want to try again        :\n");
                printf(":          Put 2 if you want to shut down        :\n");
                printf("+------------------------------------------------+\n");
                printf("Your Choice : ");
                scanf("%d", &decision);
                while(decision > 2){
                    printf("Wrong command, Try again pls\n");
                    printf("Your Choice : ");
                    scanf("%d", &decision);
                }
                switch(decision){
                    case 1: break;
                    case 2: return 0; break;
                }
                cant = 1;
                break;
                }
                else if (ch == 13){ //ENTER
                    break;
                }
                else if(ch == 8){ //BACLSPACE
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
            printf("\n\n+------------------------------+\n");
            printf("+    Are u sure to register?   +\n");
            printf("+      Put 1 if u sure         +\n");
            printf("+      Put 2 if u not sure     +\n");
            printf("+------------------------------+\n");
            printf("Your Choice : ");
            scanf("%d", &decision);
            switch(decision){
            case 1:
                system("cls");
                fwrite(&data, sizeof(data), 1, regis);
                fclose(regis);
                FILE *check;
                check = fopen("../data/check_id.txt", "ab+");
                fwrite(&id_data, sizeof(id_data), 1, check);
                fclose(check);
                printf("+-------------------------+\n");
                printf("+   Register Successful   +\n");
                printf("+-------------------------+\n");
                break;
            case 2:
                system("cls");
                intro();
            }
        }
    else{
        printf("+-------------------------------------+\n");
        printf("+           Register Failed           +\n");
        printf("+  Password and Re-Password Not same  +\n");
        printf("+        Press enter to continue      +\n");
        printf("+-------------------------------------+\n");
        char enter;
        while (enter != 13) { 
            enter = getch();}
        intro();
    }
}

int intro(){
    system("cls");
    int decision;
    printf("+----------------------------------+\n");
    printf(":    WELCOME TO NO PAID NO LIFE    :\n");
    printf(": Put 1 if this's your first time  :\n");
    printf(": Put 2 if you have an account     :\n");
    printf(": Put 3 if you want to shut down   :\n");
    printf("+----------------------------------+\n");
    printf("Your Choice : ");
    scanf("%d", &decision);
    while(decision > 3){
        printf("Wrong Command, Try Again pls\n");
        printf("Your Choice : ");
        scanf("%d", &decision);
    }
    switch(decision){
        case 1: regis(); break;
        case 2: login(); break;
        case 3: return 0; break;
    }
}

int login(){
    char id[10], idbuff[10], buffer[10], pass[10];
    int status = 0;
    printf("Your ID: ");
    scanf("%s", id);
    FILE *check;
    check = fopen("../data/check_id.txt", "rb"); // CHECK ID IN SYSTEM
    while(fread(&id_data,sizeof(id_data),1,check) == 1){
        if(strcmp(id, id_data.id_check) == 0){
            status = 1;
            break;
        }
    }
    if(status){
        strcpy(idbuff, id);
        strcpy(buffer, "../data/");
        strcat(buffer, id);
        strcat(buffer, ".csv");
        FILE *logincsv;
        logincsv = fopen(buffer, "ab+");
        int state = 0;
        int cant = 1, pos = 0;
        char ch;
        int decision;
        while(cant){
            cant = 0;
            printf("Your Password : ");
            while(1){
                ch = getch();
                if (ch == 13 && pos == 0){
                    printf("\n");
                    printf("+------------------------------------------------+\n");
                    printf(":               No Password Entered              :\n");
                    printf(":          Put 1 if you want to try again        :\n");
                    printf(":          Put 2 if you want to shut down        :\n");
                    printf("+------------------------------------------------+\n");
                    printf("Your Choice : ");
                    scanf("%d", &decision);
                    while(decision > 2){
                        printf("Wrong command, Try again pls\n");
                        printf("Your Choice : ");
                        scanf("%d", &decision);
                        }
                    switch(decision){
                        case 1: break;
                        case 2: return 0; break;
                        }
                    cant = 1;
                    break;
                    }
                else if (ch == 13){ //ENTER
                    break;
                    }
                else if(ch == 8){ //BACLSPACE
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
            printf("+-----------------------+\n");
            printf("+  LOGIN SUCCESSFUL!!!  +\n");
            printf("+-----------------------+\n");
            return 0;
        }
        else{
            printf("+------------------+\n");
            printf("+     TRY AGAIN    +\n");
            printf("+------------------+\n");
            login();
        }
    }
    else{
        printf("+-------------------------+\n");
        printf("+    NOT FOUND THIS ID    +\n");
        printf("+-------------------------+\n");
        intro();
    }
}

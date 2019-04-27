#include "stdio.h"
#include "string.h"
#include "conio.h"
#include "ctype.h"
#include "stdlib.h"

struct save{
    char id[10];      // Name
    char pass[10];      // Lastname
}data;

int intro(); //ฟังก์ชั่น Intro
int id();    //ฟังก์ชั่นเช็คว่ามี ID อยู่ในฐานข้อมูลมั้ย
int regis(); //ฟังก์ชั่นสมัครสมาชิก

int main(){
    intro();
}

int intro(){
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
        case 2: id(); break;
        case 3: return 0; break;
    }
}

int id(){
    FILE *user_text;
    user_text = fopen("../data/all_data.txt", "rb"); //Read-only mode
    int check = 0, decision, pos = 0, cantuse = 1;
    char id_login[10], ch;
    while(cantuse){
        cantuse = 0;
        printf("Your Id : ");
        while(1){
            ch = getch();
            if (ch == 13 && pos == 0){
                printf("\n");
                printf("+------------------------------------------------+\n");
                printf(":                  No ID Entered                 :\n");
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
                    case 1: id(); break;
                    case 2: return 0; break;
                }
                cantuse = 1;
                break;
            }else if (ch == 13){ //ENTER
                break;
            }else if(ch == 8){ //BACLSPACE
                if (pos > 0){ //ถ้าเป็น 0 คือยังไม่ได้กรอกพาส
                    pos--;
                    id_login[pos] == '\0';
                    printf("\b \b");}
            }
            else if (ch == 32 || ch == 9 || !isalnum(ch)){ //SPACE , TAB , SPECIAL
                continue;}
            else{
                if(pos < 10){
                    id_login[pos] = ch;
                    pos++;
                    printf("%c", ch);
                }else{
                    continue;
                }
            }}
            id_login[pos] = '\0';
        }
    printf("\n");
    int cant=1, pos2 = 0;
    char password[10], ch2;
    while(cant){
        cant = 0;
        printf("Your Password : ");
        while(1){
            ch2 = getch();
            if (ch2 == 13 && pos2 == 0){
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
            }else if (ch2 == 13){ //ENTER
                break;
            }else if(ch2 == 8){ //BACLSPACE
                if (pos2 > 0){ //ถ้าเป็น 0 คือยังไม่ได้กรอกพาส
                    pos2--;
                    password[pos2] == '\0';
                    printf("\b \b");}
            }
            else if (ch2 == 32 || ch2 == 9 || !isalnum(ch2)){ //SPACE , TAB , SPECIAL
                continue;}
            else{
                if(pos2 < 10){
                    password[pos2] = ch2;
                    pos2++;
                    printf("*");
                }else{
                    continue;
                }
            }}
            password[pos2] = '\0';
        }
    printf("\n");
    while(fread(&data,sizeof(data),1,user_text) == 1){
        if(strcmp(id_login, data.id) == 0 && strcmp(password, data.pass) == 0){
            check = 1;
            break;
        }
    }
    if(check){
        printf("\n");
        printf("+--------------------------------+\n");
        printf(":            ID Found            :\n");
        printf(":       Login Successful!!!      :\n");
        printf("+--------------------------------+\n");
        fclose(user_text);

    }
    else{
        printf("\n");
        printf("+------------------------------------------------+\n");
        printf(":                 ID not found                   :\n");
        printf(":         Put 1 if you want to register          :\n");
        printf(":         Put 2 if you want to try again         :\n");
        printf(":         Put 3 if you want to shut down         :\n");
        printf("+------------------------------------------------+\n");
        printf("Your Choice : ");
        scanf("%d", &decision);
        while(decision > 3){
            printf("Wrong command, Try again pls\n");
            printf("Your Choice : ");
            scanf("%d", &decision);
        }
        switch(decision){
            case 1: regis(); fclose(user_text); break;
            case 2: id(); break;
            case 3: return 0; break;
        }
    }      
}


int regis(){
    FILE *regis_txt;
    regis_txt = fopen("../data/all_data.txt","ab+"); // Write and Read mode
    int decision, pos = 0;
    if(regis_txt == NULL) {
        printf("Error! Check your file!");
    }
    else{
        system("cls");
        printf("Please Enter Your Information Correctly\n");
        /* USERNAME */
        printf("Username: ");
        scanf("%s", data.id);
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
                }else if (ch == 13){ //ENTER
                    break;
                }else if(ch == 8){ //BACLSPACE
                    if (pos > 0){ //ถ้าเป็น 0 คือยังไม่ได้กรอกพาส
                        pos--;
                        password[pos] == '\0';
                        printf("\b \b");}
                }
                else if (ch == 32 || ch == 9 || !isalnum(ch)){ //SPACE , TAB , SPECIAL
                    continue;}
                else{
                    if(pos < 10){
                        password[pos] = ch;
                        pos++;
                        printf("*");
                    }else{
                        continue;
                    }
                }}
                password[pos] = '\0';
            }
            printf("\n");
        /* PASSWORD */
        int cant2 = 1, pos2 = 0;
        char password2[10], ch2;
        while(cant2){
            cant2 = 0;
            printf("Re-Password : ");
            while(1){
                ch2 = getch();
                if (ch2 == 13 && pos2 == 0){
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
                    cant2 = 1;
                    break;
                }else if (ch2 == 13){ //ENTER
                    break;
                }else if(ch2 == 8){ //BACLSPACE
                    if (pos2 > 0){ //ถ้าเป็น 0 คือยังไม่ได้กรอกพาส
                        pos2--;
                        password2[pos2] == '\0';
                        printf("\b \b");}
                }
                else if (ch2 == 32 || ch2 == 9 || !isalnum(ch2)){ //SPACE , TAB , SPECIAL
                    continue;}
                else{
                    if(pos2 < 10){
                        password2[pos2] = ch2;
                        pos2++;
                        printf("*");
                    }else{
                        continue;
                    }
                }}
                password2[pos2] = '\0';
            }
            printf("\n");
            if(strcmp(password, password2) == 0){
                strcpy(data.pass, password);
                printf("+------------------------------+\n");
                printf("+    Are u sure to register?   +\n");
                printf("+      Put 1 if u sure         +\n");
                printf("+      Put 2 if u not sure     +\n");
                printf("+------------------------------+\n");
                printf("Your Choice : ");
                scanf("%d", &decision);
                switch(decision){
                case 1:
                    system("cls");
                    fwrite(&data, sizeof(data), 1, regis_txt);
                    fclose(regis_txt);
                    printf("+-------------------------+\n");
                    printf("+   Register Successful   +\n");
                    printf("+-------------------------+\n");
                    intro();
                    break;
                case 2:
                    intro();
                    break;
                }
            }
            else{
                printf("Password and Re-Password Not same\n");
                intro();
            }
    }
}
#include "stdio.h"
#include "string.h"
#include "conio.h"
#include "ctype.h"
int intro(); //ฟังก์ชั่น Intro
int id();    //ฟังก์ชั่นเช็คว่ามี ID อยู่ในฐานข้อมูลมั้ย
int pass();  //ฟังก์ชั่นเช็คว่ามี Password อยู่ในฐานข้อมูลมั้ย
int regis(); // ฟังก์ชั่นสมัครสมาชิก

int main(){
    intro();
}

int intro(){
    int decision;
    printf("+----------------------------------+\n");
    printf(":    WELCOME TO NO PAID NO LIFE    :\n");
    printf(": Put 1 If this's your first time  :\n");
    printf(": Put 2 If you have an account     :\n");
    printf(": Put 3 if you want to shut down   :\n");
    printf("+----------------------------------+\n");
    printf("Your Choice : ");
    scanf("%d", &decision);
    while(decision > 3){
        printf("Wrong Command, Try Again pls\n");
        scanf("%d", &decision);
    }
    switch(decision){
        case 1: regis(); break;
        case 2: id(); break;
        case 3: return 0; break;
    }
}

int id(){
    FILE *id_csv;
    id_csv = fopen("../data/id.csv", "a+");
    int check = 0, decision;
    char id[10], buffer_id[10];
    printf("ENTER ID : ");
    scanf("%s", id);
    fscanf(id_csv, "%s", buffer_id);
    while(strcmp(buffer_id, "END") != 0){
        fscanf(id_csv, "%s", buffer_id);
        if(strcmp(buffer_id, id) == 0){
            check = 1;
        }
    }
    if(check){
        fclose(id_csv);
        pass();
    }
    else{
        printf("+------------------------------------------------+\n");
        printf(": This user not found. Did you want to register? :\n");
        printf(":         Put 1 if you want to register          :\n");
        printf(":         Put 2 if you want to log in again      :\n");
        printf(":         Put 3 if you want to shut down         :\n");
        printf("+------------------------------------------------+\n");
        scanf("%d", &decision);
        while(decision > 3){
           printf("WRONG COMMAND TRY AGAIN PLZ\n");
           scanf("%d", &decision);
        }
        switch(decision){
            case 1: regis(); fclose(id_csv); break;
            case 2: main(); break;
            case 3: return 0; break;
        }      
    }
}

int pass(){
    FILE *pass_csv;
    pass_csv = fopen("../data/pass.csv", "a+");
    int check = 0;
    char password[10], buffer_pass[10];
    printf("ENTER PASSWORD : ");
    scanf("%s", password);
    fscanf(pass_csv, "%s", buffer_pass);
    while(strcmp(buffer_pass, "END") != 0){
        fscanf(pass_csv, "%s", buffer_pass);
        if(strcmp(buffer_pass, password) == 0){
            check = 1;
        }
    }
    if(check){
        fclose(pass_csv);
        printf("LOGIN SUCCESSFUL!\n");
        return 0;
    }
    else{
        printf("WRONG PASSWORD TRY AGAIN\n");
        pass();
    }
}

int regis(){
    FILE *regis_idcsv;
    regis_idcsv = fopen("../data/id.csv", "a");
    char id_regis[10], ch;
    int cantuse = 1, pos =0;
    while(cantuse){
        cantuse = 0;
        printf("Your Id : ");
        // scanf("%s",id_regis);
        while(1){
            ch = getch();
            if (ch == 13 && pos == 0){
                printf("\nPlease Enter the ID\n");
                cantuse = 1;
                break;
            }else if (ch == 13){ //ENTER
                break;
            }else if(ch == 8){ //BACLSPACE
                if (pos > 0){ //ถ้าเป็น 0 คือยังไม่ได้กรอกพาส
                    pos--;
                    id_regis[pos] == '\0';
                    printf("\b \b");}
            }
            else if (ch == 32 || ch == 9 || !isalnum(ch)){ //SPACE , TAB , SPECIAL
                continue;}
            else{
                if(pos < 10){
                    id_regis[pos] = ch;
                    pos++;
                    printf("%c", ch);
                }else{
                    continue;
                }
            }}
            id_regis[pos] = '\0';
            printf("\n");
            fprintf(regis_idcsv, "\n%s", id_regis);
            fclose(regis_idcsv);
        }

    FILE *regis_passcsv;
    regis_passcsv = fopen("../data/pass.csv", "a+");
    char pass_regis[10], pass_check[10];
    pos = 0; // reuse variable
    cantuse = 1; // aka notsame

    while(cantuse){
        printf("Password : ");
        while(1){
            ch = getch();
            if (ch == 13 && pos == 0){
                printf("\nPlease Enter your password\n");
                cantuse = 1;
                break;
            }else if (ch == 13){ //ENTER
                break;
            }
            else if(ch == 8){
                if (pos > 0){ //ถ้าเป็น 0 คือยังไม่ได้กรอกพาส
                    pos--;
                    pass_regis[pos] == '\0';
                    printf("\b \b");}
            }
            else if (ch == 32 || ch == 9 || !isalnum(ch)){ //SPACE , TAB
                continue;}
            else
            {
                if(pos < 10){
                    pass_regis[pos] = ch;
                    pos++;
                    printf("*");
                }else{
                    continue;
                }
            }
        }
        pass_regis[pos] = '\0';
        pos = 0;
        printf("\n");

        printf("Re-Password : ");
        while(1){
            ch = getch();
            if (ch == 13 && pos == 0){
                printf("\nPlease Enter your re-password\n");
                cantuse = 1;
                break;
            }else if (ch == 13){ //ENTER
                break;
            }
            else if(ch == 8){
                if (pos > 0){ //ถ้าเป็น 0 คือยังไม่ได้กรอกพาส
                    pos--;
                    pass_check[pos] == '\0';
                    printf("\b \b");}
            }
            else if (ch == 32 || ch == 9 || !isalnum(ch)){ //SPACE , TAB
                continue;}
            else
            {
                if(pos < 10){
                    pass_check[pos] = ch;
                    pos++;
                    printf("*");
                }else{
                    continue;
                }
            }
        }
        pass_check[pos] = '\0';
        printf("\n");
        
        // ***** เหลือ add function กดย้อนกลับในโปรแกรมจะได้ไม่ต้องยุ่งยากเปิดโปรแกรมปิดใหม่ *********
        if(strcmp(pass_regis, pass_check) == 0){
            cantuse = 0;
            fprintf(regis_passcsv, "%s", pass_check);
            fclose(regis_passcsv);
            printf("REGISTER success!\n");
        }else{
            printf("Password and Re-password are not the same.Pls Enter again.\n");
        }
    
}}
#include "stdio.h"
#include "string.h"
#include "conio.h"
int intro(); //ฟังก์ชั่น Intro
int id();    //ฟังก์ชั่นเช็คว่ามี ID อยู่ในฐานข้อมูลมั้ย
int pass();  //ฟังก์ชั่นเช็คว่ามี Password อยู่ในฐานข้อมูลมั้ย
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
    char id_login[10], buffer_id[10];
    printf("ENTER ID : ");
    scanf("%s", id_login);
    fscanf(id_csv, "%s", buffer_id);
    while(strcmp(buffer_id, "END") != 0){
        fscanf(id_csv, "%s", buffer_id);
        if(strcmp(buffer_id, id_login) == 0){
            check = 1;
        }
    }
    if(strlen(id_login) == 0){
        printf("+------------------------------------------------+\n");
        printf(":                  No ID Entered                 :\n");
        printf(":          Put 1 if you want to try again        :\n");
        printf(":          Put 2 if you want to shut down        :\n");
        printf("+------------------------------------------------+\n");
        printf("Your Choice : ");
        scanf("%d", &decision);
        while(decision > 2){
            printf("Wrong command, Try again pls\n");
            scanf("%d", &decision);
        }
        switch(decision){
            case 1: id(); break;
            case 2: return 0; break;
        }
    }
    else if(check){
        printf("+--------------------------------+\n");
        printf(":            ID Found            :\n");
        printf(":       Enter your password      :\n");
        printf("+--------------------------------+\n");
        fclose(id_csv);
        pass();
    }
    else if(check == 0){
        printf("+------------------------------------------------+\n");
        printf(":                 ID not found                   :\n");
        printf(":         Put 1 if you want to register          :\n");
        printf(":         Put 2 if you want to log in again      :\n");
        printf(":         Put 3 if you want to shut down         :\n");
        printf("+------------------------------------------------+\n");
        printf("Your Choice : ");
        scanf("%d", &decision);
        while(decision > 3){
            printf("Wrong command, Try again pls\n");
            scanf("%d", &decision);
        }
        switch(decision){
            case 1: regis(); fclose(id_csv); break;
            case 2: id(); break;
            case 3: return 0; break;
        }
    }      
}


int pass(){
    FILE *pass_csv;
    pass_csv = fopen("../data/pass.csv", "a+");
    int check = 0, decision;
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
    if(strlen(password) == 0){
        printf("+------------------------------------------------+\n");
        printf(":               No Password Entered              :\n");
        printf(":          Put 1 if you want to try again        :\n");
        printf(":          Put 2 if you want to shut down        :\n");
        printf("+------------------------------------------------+\n");
        printf("Your Choice : ");
        scanf("%d", &decision);
        while(decision > 2){
            printf("Wrong command, Try again pls\n");
            scanf("%d", &decision);
        }
        switch(decision){
            case 1: pass(); break;
            case 2: return 0; break;
        }
    }
    else if(check){
        fclose(pass_csv);
        printf("+--------------------------------+\n");
        printf(":        Login Successful!       :\n");
        printf("+--------------------------------+\n");
        return 0;
    }
    else if(check == 0){
        printf("+--------------------------------------------+\n");
        printf(":              Wrong password                :\n");
        printf(":    Put 1 if you want to try again          :\n");
        printf(":    Put 2 if you want to go to main menu    :\n");
        printf("+--------------------------------------------+\n");
        printf("Your Choice : ");
        scanf("%d", &decision);
        while(decision > 2){
            printf("Wrong command, Try again pls\n");
            scanf("%d", &decision);
        }
        switch(decision){
        case 1: pass(); break;
        case 2: main(); break;
        }
    }
}

int regis(){
    FILE *regis_idcsv;
    regis_idcsv = fopen("../data/id.csv", "a+");
    char id_regis[10];
    printf("Your ID : ");
    scanf("%s", id_regis);
    fprintf(regis_idcsv, "%s\n", id_regis);
    fclose(regis_idcsv);
    FILE *regis_passcsv;
    regis_passcsv = fopen("../data/pass.csv", "a+");
    char pass_regis[10];
    printf("Your Password : ");
    scanf("%s", pass_regis);
    fprintf(regis_passcsv, "%s\n", pass_regis);
    printf("REGISTER SUCCESSFUL!\n");
    printf("PLEASE LOG IN AGAIN !\n");
    id();
}
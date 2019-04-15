#include "stdio.h"
#include "string.h"
#include "conio.h"

int id();    //ฟังก์ชั่นเช็คว่ามี ID อยู่ในฐานข้อมูลมั้ย
int pass();  //ฟังก์ชั่นเช็คว่ามี Password อยู่ในฐานข้อมูลมั้ย
int regis(); // ฟังก์ชั่นสมัครสมาชิก

int main(){
    id();
}

int id(){
    FILE *id_csv;
    id_csv = fopen("id.csv", "a+");
    int check = 0, decision;
    char id[10], buffer_id[10];
    printf("ENTER ID :");
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
        printf("+------------------------------------------------+\n");
        scanf("%d", &decision);
        while(decision > 2){
           printf("WRONG COMMAND TRY AGAIN PLZ\n");
           scanf("%d", &decision);
        }
        switch(decision){
            case 1: regis(); fclose(id_csv); break;
            case 2: main(); break;
        }      
    }
}

int pass(){
    FILE *pass_csv;
    pass_csv = fopen("pass.csv", "a+");
    int check = 0;
    char password[10], buffer_pass[10];
    printf("ENTER PASSWORD :");
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
    regis_idcsv = fopen("id.csv", "a+");
    char id_regis[10];
    printf("Your ID: ");
    scanf("%s", id_regis);
    fprintf(regis_idcsv, "%s\n", id_regis);
    fclose(regis_idcsv);
    FILE *regis_passcsv;
    regis_passcsv = fopen("pass.csv", "a+");
    char pass_regis[10];
    printf("Your Password: ");
    scanf("%s", pass_regis);
    fprintf(regis_passcsv, "%s\n", pass_regis);
    printf("REGISTER SUCCESSFUL!\n");
    main();
    //printf("CURRENT ID IS : %s\n", id_regis);
    //printf("CURRENT PASSWORD IS : %s\n", pass_regis);
    //printf("PLEASE LOG IN AGAIN !\n");
}
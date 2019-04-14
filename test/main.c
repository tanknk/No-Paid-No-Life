#include "stdio.h"
#include "string.h"
#include "conio.h"
struct data{
    char id_x[10], pass_x[10];
};

main(){
    FILE *log;
    log = fopen("login.csv", "r");
    int range = 10 , fail_login = 1;
    char id[range], pass[range], buffer[range];
    char ch; // ตัวแปรเก็บแต่ละตัวของพาสเวิร์ด
    int passposition = 0, answer = 0; //นับจำนวนพาสเวิร์ดที่กรอกเข้ามา
    printf("ENTER ID :");
    scanf("%s", id);
    printf("ENTER PASSWORD :");
    scanf("%s", pass);
    fscanf(log, "%s", buffer);
    // fscanf(log, "%s", buffer);
    // printf("THIS IS BUFFER > %s\n", buffer);
    // fscanf(log, "%s", buffer);
    // printf("THIS IS BUFFER > %s\n", buffer);
    // fscanf(log, "%s", buffer);
    // printf("THIS IS BUFFER > %s\n", buffer);
    while (strcmp(buffer, "end") != 0){
        fscanf(log, "%s", buffer);
        // printf("THIS IS BUFFER > %s\n", buffer);
        // printf("buffer is %s and ID is %s\n", buffer, id);
        if (strcmp(buffer, id) == 0){
            answer = 1;
        }
    }
    if(answer==1){
        printf("success");
    }
    else{
        printf("failed");
    }
    fclose(log);
}
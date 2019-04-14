#include "stdio.h"
#include "string.h"
#include "conio.h"

main(){
    FILE *log;
    log = fopen("login.csv", "r");
    int range = 10 , fail_login = 1;
    char id[range], pass[range], buffer[range];
    char ch; // ตัวแปรเก็บแต่ละตัวของพาสเวิร์ด
    int passposition = 0; //นับจำนวนพาสเวิร์ดที่กรอกเข้ามา
    printf("ENTER ID :");
    scanf("%s", id);
    printf("ENTER PASSWORD :");
    scanf("%s", pass);
    fscanf(log, "%s", buffer);
    printf("THIS IS BUFFER > %s\n", buffer);
    fscanf(log, "%s", buffer);
    printf("THIS IS BUFFER > %s\n", buffer);
    fclose(log);
}
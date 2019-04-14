#include "stdio.h"
#include "string.h"
#include "conio.h"

main(){
    int maxidandpass = 15, fail_login = 1;
    char id[maxidandpass], pass[maxidandpass];
    char ch; // ตัวแปรเก็บแต่ละตัวของพาสเวิร์ด
    int passposition = 0; //นับจำนวนพาสเวิร์ดที่กรอกเข้ามา

    printf("WELCOME\n");
    printf("R for Register\n");
    printf("L for Login\n");

    char status;
    int sta = 1;
    scanf("%c", &status);

    while(sta){
        if (status == 'R'){
            printf("Register\n");
            break;
        }
        else if (status == 'L')
        {
            printf("Login\n\n");

            while (fail_login){
                printf("\n");
                printf("ENTER YOUR ID : ");
                scanf("%s", id);
                printf("ENTER YOUR PASSWORD : ");
                while(1){
                    ch = getch(); //รับ input จากคีย์บอร์ดหนึ่งตัวโดยไม่แสดงบทหน้าจอ
                    if (ch == 13){ // ASCII 13 คือ ENTER
                        break;}
                    else if (ch == 8){// backspace
                        if(passposition > 0){ // ถ้าเป็น 0 คือยังไม่ได้กรอกพาสเวิร์ด ลบก็ไม่มีผลอะไรอยู่แล้ว
                            passposition--;
                            pass[maxidandpass] = '\0';
                            printf("\b \b"); //ย้อนกลับสองครั้งเพราะตำแหน่งที่แสดงผลบนจอคือตำแหน่งถัดไป
                        }}
                    else if (ch == 32 || ch == 9){ // spacebar , tab
                        continue;
                    }else
                    {
                        if (passposition < maxidandpass){
                            pass[passposition] = ch;
                            passposition++;
                            printf("*");
                        }
                        else
                        {
                            printf("\nYOUR PASSWORD IS TOO LONG. TRY TO ENTER AGAIN");
                            break;
                        }
                        
                    }
                    pass[passposition] = '\0';
                    if (strlen(pass) == 0 || pass == NULL){ //เงื่อนไขนี้ไม่ปรากฏ (needed fix)
                        printf("\nNo Password Entered"); 
                    }else
                    {
                        fail_login = 0;
                    }
                    }}
            
            printf("\nLOGIN SUCCESS!");
            break; 
        }
        else {
            printf("\nPlease ENTER Again\n");
            printf("R for Register\n");
            printf("L for Login\n");
            scanf("%c", &status);
        }
        
    }
    
    
}
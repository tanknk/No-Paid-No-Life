#include "stdio.h"
#include "string.h"
#include "conio.h"

int pass();

int main(){
    FILE *id_csv;
    id_csv = fopen("id.csv", "r");
    int check = 0;
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
        printf("TRY AGAIN\n");
        main();
    }
}

int pass(){
    FILE *pass_csv;
    pass_csv = fopen("pass.csv", "r");
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
    }
    else{
        printf("WRONG PASSWORD TRY AGAIN\n");
        pass();
    }
}
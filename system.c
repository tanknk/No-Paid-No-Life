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

int main(){
    system("cls");
    // Username
    printf("Enter username: ");
    char username[10]; 
    scanf(" %s", username);
    // Filename (Maximun line size: 200)
    char filename[30];
    strcpy(filename, "./data/wallet/");
    strcat(filename, username);
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
    return 0;
}

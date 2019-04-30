#ifndef COMPONENT_H
#define COMPONENT_H

typedef struct{
    char date[11];  // 1st Column: Date (YYYY-MM-DD)
    double amount;  // 2nd Column: [+/-] Amount (Initial Balance for 1st Row)
    char cat[4];    // 3rd Column: Catagory (Currencyfor 1st Row)
    char note[101]; // 4th Column: Note
}DATA;

typedef struct{
    char code[4];   // Catagory Code
    char name[20];  // Catagory Name
}CAT;

#endif

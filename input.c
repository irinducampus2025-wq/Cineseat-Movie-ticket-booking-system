#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include "input.h"


char *getLine(char *buffer , int size) {
    if (fgets(buffer, size, stdin)== NULL){
        return NULL;
    }
    buffer[strcspn(buffer,"\n")]=0;
    return buffer;

}

int getIntBetween(const char *prompt,int min,int max) {
    int value;
    char raw[100];

    while (1){
        printf("%s",prompt);

        if (!getLine(raw,sizeof(raw))){
            exit(0);
        }

        if (sscanf(raw,"%d",&value)== 1 &&
            value>=min &&
            value<=max){
            return value;
        }
        printf("Invalid input. Please enter a number between %d and %d.\n", min, max);
    }

}

int getYesNo(const char *prompt){
    char answer[10];

    printf("%s (y/n): ",prompt);
    getLine(answer,sizeof(answer));

    return (answer[0]== 'y'|| answer[0]=='Y');

}

void pauseForUser(void){
    char discard[10];

    printf("\nPress Enter to go back to the menu...");
    getLine(discard,sizeof(discard));
}



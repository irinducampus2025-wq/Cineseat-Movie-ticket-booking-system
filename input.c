#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <ctype.h>
#include "input.h"

#define CLR_RESET  "\033[0m"
#define CLR_WARN   "\033[1;33m"
#define CLR_ERR    "\033[1;31m"

int getLine(char *buf , int len) {
    if (!fgets(buf, len, stdin))return 0;
    size_t n = strlen(buf);
    if (n>0 && buf[n - 1] =='\n') {
        buf[n-1] = '\0';
    }else {
        int ch;
        while ((ch = getchar()) != '\n'&& ch != EOF){}
    }
    return 1;
}

int getIntBetween(const char *msg,int lo,int hi) {
    char raw[100];
    for (;;){
        printf(CLR_WARN "%s" CLR_RESET,msg);
        if (!getline(raw,sizeof(raw))) {
            printf(CLR_ERR "\nNo more input - closing program.\n" CLR_RESET);
            exit 0;
        }
        char *start = raw;
        while (isspace((unsigned char)*start )) start++;
        if ( * start == '\0') {
            printf(CLR_ERR "Please type a number.\n "CLR_RESET);
            continue;
        }
       char *stop;
       long n = strtol(start,&stop,10);
       while (isspace((unsigned char)*stop)) stop++;
       if (*stop != '\0') {
          printf(CLR_ERR "Number only, please.\n"CLR_RESET);
          continue;
       }
       if (n< lo || n> hi){
        printf(CLR_ERR "That has to betweeen %d and %d.\n"CLR_RESET,lo,hi);
        continue;
       }
       return (int)n;

    }
}

int getYesNo(const char *msg){
    char raw[20];
    for (;;){
        printf(CLR_WARN "%s" CLR_RESET,msg);
        if (!getLine(raw ,sizeof(raw))){
            printf(CLR_ERR "\nNo more input - closing program.\n" CLR_RESET);
            exit(0);
        }
        if (raw[0] == 'y' || raw[0] == 'Y') return 1;
        if (raw[0] == 'n' || raw[0] == 'N') return 0;
        printf(CLR_ERR "Type y or n.\n" CLR_RESET);
    }
}



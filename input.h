#ifndef INPUT_H
#define INPUT_H

#include "types.h"


int getIntBetween(const char *prompt,int min,int max);
char *getLine(char *buffer,int size);
int getYesNo(const char *prompt);
void pauseForUser(void);


#endif

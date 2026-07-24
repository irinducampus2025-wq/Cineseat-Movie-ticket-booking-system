#ifndef DISPLAY_H
#define DISPLAY_H

#include "types.h"



void banner(const char *text);
void screenMenu(void);
void screenFilmList(void);



int pickShow(int *f,int *sh);

void screenSeatGrid(int f,int sh);

#endif

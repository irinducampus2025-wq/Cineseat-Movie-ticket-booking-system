#ifndef BOOKING_H
#define BOOKING_H


int parseSeatCode(const char *code, int *row, int *col);

void actionBook(void);
void actionCancel(void);

#endif 

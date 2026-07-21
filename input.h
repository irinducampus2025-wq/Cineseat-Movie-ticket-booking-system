#ifndef DATA_H
#define DATA_H

#include "types.h"



extern Movie movies[NUM_MOVIES];


void initMovies(void);

SeatTier tierForRow(int rowIndex);


int isValidSeat(int row, int col);

#endif

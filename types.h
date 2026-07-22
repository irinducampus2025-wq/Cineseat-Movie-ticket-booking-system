#ifndef TYPES_H
#define TYPES_H


#define MAX_FILMS      3
#define SHOWS_PER_FILM 2
#define SEAT_ROWS      5
#define SEAT_COLS      10
#define NAME_LEN       50

typedef enum { TIER_REGULAR, TIER_PREMIUM, TIER_VIP } Tier;

typedef struct {
    int    taken;
    char   bookedBy[NAME_LEN];
    double amountPaid;
    int    studentFlag;
    int    seniorFlag;
    int    groupFlag;
} Ticket;

typedef struct {
    char   time[20];
    Ticket seats[SEAT_ROWS][SEAT_COLS];
    int    soldCount;
    double earnings;
} Show;

typedef struct {
    char title[60];
    Show shows[SHOWS_PER_FILM];
} Film;

extern Film films[MAX_FILMS];

#endif 

#include <stdio.h>
#include "types.h"
#include "catalog.h"

Film films[MAX_FILMS];

void loadCatalog(void) {
    static const char *names[MAX_FILMS] = {
        "Inception Reborn", "Galaxy Raiders", "The Last Symphony"
    };
    static const char *slots[MAX_FILMS][SHOWS_PER_FILM] = {
        { "10:00 AM", "6:30 PM" },
        { "1:00 PM",  "9:00 PM" },
        { "11:30 AM", "4:00 PM" }
    };

    for (int f = 0; f < MAX_FILMS; f++) {
        snprintf(films[f].title, sizeof(films[f].title), "%s", names[f]);
        for (int s = 0; s < SHOWS_PER_FILM; s++) {
            Show *sh = &films[f].shows[s];
            snprintf(sh->time, sizeof(sh->time), "%s", slots[f][s]);
            sh->soldCount = 0;
            sh->earnings  = 0.0;
            for (int r = 0; r < SEAT_ROWS; r++) {
                for (int c = 0; c < SEAT_COLS; c++) {
                    Ticket *tk = &sh->seats[r][c];
                    tk->taken = 0;
                    tk->bookedBy[0] = '\0';
                    tk->amountPaid = 0.0;
                    tk->studentFlag = 0;
                    tk->seniorFlag = 0;
                    tk->groupFlag = 0;
                }
            }
        }
    }
}

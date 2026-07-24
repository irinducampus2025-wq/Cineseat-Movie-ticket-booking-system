#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "types.h"
#include "input.h"
#include "display.h"
#include "search.h"
#include <ctype.h>
#include <stdlib.h>


#define CLR_RESET "\033[0m"
#define CLR_OK    "\033[1;32m"
#define CLR_WARN  "\033[1;33m"
#define CLR_ERR   "\033[1;31m"

void actionFind(void) {
    banner("SEARCH");
    printf("1) By name   2) By seat\n");
    int mode = getIntBetween("Pick: ", 1, 2);

    if (mode == 1) {
        char query[NAME_LEN];
        printf(CLR_WARN "Name contains: " CLR_RESET);
        getLine(query, sizeof(query));

        int hits = 0;
        for (int f = 0; f < MAX_FILMS; f++)
            for (int s = 0; s < SHOWS_PER_FILM; s++)
                for (int r = 0; r < SEAT_ROWS; r++)
                    for (int c = 0; c < SEAT_COLS; c++) {
                        Ticket *tk = &films[f].shows[s].seats[r][c];
                        if (tk->taken && strstr(tk->bookedBy, query)) {
                            printf(CLR_OK "%s - %s (%s) seat %c%d - Rs. %.2f\n" CLR_RESET,
                                   tk->bookedBy, films[f].title, films[f].shows[s].time,
                                   'A' + r, c + 1, tk->amountPaid);
                            hits++;
                        }
                    }
        if (!hits) printf(CLR_ERR " Nothing matched \"%s\".\n" CLR_RESET, query);

    } else {
        int f, s;
        pickShow(&f, &s);
        char code[20];
        printf(CLR_WARN "Seat: " CLR_RESET);
        if (!getLine(code, sizeof(code))) { 
            printf(CLR_ERR "\nClosing.\n" CLR_RESET); 
            exit(0); 
        }
        int r, c;
        if (!parseSeatCode(code, &r, &c)) { 
            printf(CLR_ERR " Not a valid seat.\n" CLR_RESET); 
            return; 
        }
        Ticket *tk = &films[f].shows[s].seats[r][c];
        if (!tk->taken) { 
            printf(CLR_ERR " %c%d is still free.\n" CLR_RESET, 'A' + r, c + 1);
            return; 
        }
        printf(CLR_OK "%c%d -> %s, paid Rs. %.2f\n" CLR_RESET, 
               'A' + r, c + 1, tk->bookedBy, tk->amountPaid);
    }
}


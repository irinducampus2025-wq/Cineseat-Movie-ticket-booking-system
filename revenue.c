#include <stdio.h>
#include "types.h"
#include "display.h"
#include "revenue.h"

#define CLR_RESET  "\033[0m"
#define CLR_TITLE  "\033[1;36m"

void actionSummary(void) {
    banner("REVENUE REPORT");
    int    totalTickets = 0;
    double totalEarn    = 0.0;

    for (int f = 0; f< MAX_FILMS; f++){
        for (int s = 0; s < SHOWS_PER_FILM; s++) {
                show *sh = &films[f].shows[s];
        printf(" %20s %-10s  -> %2d sold,Rs. %.2f\n",
               films[f].title,sh->time, sh->soldCount, sh->earnings );
        totalTickets += sh->soldCount;
        totalEarn    += sh->earnings;
        }
    }
    printf(CLR_TITLE "  -----------------------------------------\n" CLR_RESET);
    printf(CLR_TITLE "  TOTAL: %d sold, Rs.%2f\n" CLR_RESET, totalTickets, totalEarn);
}

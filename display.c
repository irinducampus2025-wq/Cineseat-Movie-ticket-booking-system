#include <stdio.h>
#include "types.h"
#include "input.h"
#include "pricing.h"
#include "display.h"

#define CLR_RESET "\033[0m"
#define CLR_TITLE "\033[1;36m"
#define CLR_OK    "\033[1;32m"
#define CLR_ERR   "\033[1;31m"
#define CLR_INFO  "\033[0;35m"

void banner (cost char *text){
    printf("\n"CLR_TITLE"== %s ==" CLR_RESET "\n",text);
}

void screenMenu(void){
    printf("\n"CLR_TITLE "#########################################"CLR_RESET"\n");
    printf(CLR_TITLE "  MOVIE TICKET BOOKING SYSTEM" CLR_RESET "\n");
    printf(CLR_TITLE "#######################################"CLR_RESET);
    printf(CLR_OK " 1)" CLR_RESET " View Showtimes\n"};
    printf(CLR_OK " 2)" CLR_RESET " View Seat Map\n");
    printf(CLR_OK " 3)" CLR_RESET " Boook a Seat\n");
    printf(CLR_OK " 4)" CLR_RESET " Cancel a Booking\n");
    printf(CLR_OK " 5)" CLR_RESET " Search Booking\n");
    printf(CLR_OK " 6)" CLR_RESET " Revenue Report\n");
    printf(CLR_OK " 7)" CLR_RESET " Exit\n");
}

void screenFilmList(void) {
    banner("NOW SHOWING");
    for (int f=0; f< MAX_FILMS;f++){
        printf(CLR_INFO "%d. %s"CLR_RESET "\n", f+1,films[f].title);
        for (int s =0; s< SHOWS_PER_FILMS;s++)
            printf("       (%d) %s\n",s+1,films[f].shows[s].time);
    }
}

int pickShow(int *f,int *sh){
    screenFilmList();
    *f  =getIntBetween("Movie #: ",1,MAX_FILMS) -1;
    *sh =getIntBetween("Showtime #: ",1,SHOWS_PER_FILM) -1;
    return 1;
}

void screenSeatGrid(int f,int sh){
     Show *s = &films[f].shows[sh];
     banner("SEAT MAP");
     printf("%s | %s\n",films[f].title,s ->time);
     printf("[ . free ]  [ " CLR_ERR "X" CLR_RESET "taken ]  A-B Regular / c-D Premium / E VIP\n\n");

     printf("      ");
     for (int c =0 ; c< SEAT_COLS; c++) printf("%2d ", c+1);
     printf("\n");

     for (int r=0; r< SEAT_ROWS; r++){
        printf(" %c |  ", 'A' + r);
        for (int c=0; c< SEAT_COLS; c++){
            if (s ->seats[r][c].taken)
                printf(CLR_ERR" X " CLR_RESET);
            else
                printf(CLR_OK"  . " CLR_RESET);

        }
        printf(" %s\n",tierLabel(tierOf(r)));
     }
}

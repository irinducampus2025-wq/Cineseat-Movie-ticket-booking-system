#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <ctype.h>
#include "types.h"
#include "input.h"
#include "display.h"
#include "pricing.h"
#include "booking.h"



#define CLR_RESET  "\033[0m"
#define CLR_TITLE  "\033[1;36m"
#define CLR_OK     "\033[1;32m"
#define CLR_WARN   "\033[1;33m"
#define CLR_ERR    "\033[1;31m"
#define CLR_INFO   "\033[0;35m"

int parseSeatCode(const char *code, int *row, int *col) {
    if (strlen(code) < 2) return 0;
    int r = toupper((unsigned char)code[0]) - 'A';
    for (size_t i = 1; i < strlen(code); i++)
        if (!isdigit((unsigned char)code[i])) return 0;
    int c = atoi(code + 1) - 1;
    if (r < 0 || r >= SEAT_ROWS || c < 0 || c >= SEAT_COLS) return 0;
    *row = r; *col = c;
    return 1;
}

void actionBook(void) {
    int f, sh;
    pickShow(&f, &sh);
    Show *s = &films[f].shows[sh];
    screenSeatGrid(f, sh);

    int want = getIntBetween("Seats to buy in this order (1-10): ", 1, 10);
    int rowsPicked[10], colsPicked[10], have = 0;

    while (have < want) {
        char code[20];
        printf(CLR_WARN "  Seat %d/%d (e.g. C5): " CLR_RESET, have + 1, want);
        if (!getLine(code, sizeof(code))) { printf(CLR_ERR "\nClosing.\n" CLR_RESET); exit(0); }

        int r, c;
        if (!parseSeatCode(code, &r, &c)) {
            printf(CLR_ERR "  That's not a valid seat on this map.\n" CLR_RESET);
            continue;
        }
        if (s->seats[r][c].taken) {
            printf(CLR_ERR "  %c%d is already sold.\n" CLR_RESET, 'A' + r, c + 1);
            continue;
        }
        int repeat = 0;
        for (int i = 0; i < have; i++)
            if (rowsPicked[i] == r && colsPicked[i] == c) repeat = 1;
        if (repeat) {
            printf(CLR_ERR "  You already picked %c%d.\n" CLR_RESET, 'A' + r, c + 1);
            continue;
        }
        rowsPicked[have] = r; colsPicked[have] = c; have++;
    }

    char buyer[NAME_LEN];
    printf(CLR_WARN "  Name on the booking: " CLR_RESET);
    getLine(buyer, sizeof(buyer));
    if (buyer[0] == '\0') snprintf(buyer, sizeof(buyer), "Guest");

    int senior  = getYesNo("  Senior citizen? (y/n): ");
    int student = senior ? 0 : getYesNo("  Student? (y/n): ");
    int group   = (want >= 4);
    if (group) printf(CLR_INFO "  Group rate unlocked (4+ seats).\n" CLR_RESET);

    double orderTotal = 0.0;
    for (int i = 0; i < have; i++) {
        int r = rowsPicked[i], c = colsPicked[i];
        Tier t = tierOf(r);
        double price = priceFor(t, student, senior, group);

        Ticket *tk = &s->seats[r][c];
        tk->taken = 1;
        snprintf(tk->bookedBy, sizeof(tk->bookedBy), "%s", buyer);
        tk->amountPaid  = price;
        tk->studentFlag = student;
        tk->seniorFlag  = senior;
        tk->groupFlag   = group;

        s->soldCount++;
        s->earnings += price;
        orderTotal  += price;

        printf(CLR_OK "  -> %c%d confirmed for %s: Rs. %.2f\n" CLR_RESET,
               'A' + r, c + 1, buyer, price);
    }
    printf(CLR_TITLE "  Order total: Rs. %.2f (%d seat(s))\n" CLR_RESET, orderTotal, have);
}

void actionCancel(void) {
    int f, sh;
    pickShow(&f, &sh);
    Show *s = &films[f].shows[sh];
    screenSeatGrid(f, sh);

    char code[20];
    printf(CLR_WARN "Seat to release (e.g. C5): " CLR_RESET);
    if (!getLine(code, sizeof(code))) { printf(CLR_ERR "\nClosing.\n" CLR_RESET); exit(0); }

    int r, c;
    if (!parseSeatCode(code, &r, &c)) {
        printf(CLR_ERR "  Not a real seat on this map.\n" CLR_RESET);
        return;
    }
    Ticket *tk = &s->seats[r][c];
    if (!tk->taken) {
        printf(CLR_ERR "  %c%d isn't booked - nothing to release.\n" CLR_RESET, 'A' + r, c + 1);
        return;
    }
    double back = tk->amountPaid;
    tk->taken = 0;
    tk->bookedBy[0] = '\0';
    tk->amountPaid = 0.0;
    tk->studentFlag = tk->seniorFlag = tk->groupFlag = 0;
    s->soldCount--;
    s->earnings -= back;

    printf(CLR_OK "  %c%d released. Rs. %.2f removed from revenue.\n" CLR_RESET, 'A' + r, c + 1, back);
}

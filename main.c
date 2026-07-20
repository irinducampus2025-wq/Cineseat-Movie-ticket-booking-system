#include<stdio.h>
#include"types.h"
#include"input.h"
#include"catalog.h"
#include"display.h"
#include"pricing.h"
#include"booking.h"
#include"search.h"
#include"revenue.h"

#define CLR_RESET "\033[0m"
#define CLR_TITLE "\033[1;36m"

void screenmenu()
{
    printf(CLR_TITLE"\nWelcome to the Movie Ticket Booking System\n"CLR_RESET);
    printf("1. View Films showtimes\n");
    printf("2. View seat Map\n ");
    printf("3. Book a ticket\n");
    printf("4. cancel a tocket\n");
    printf("5. search a booking\n");
    printf("6. View Revenue Report\n");
    printf("7. Exit\n");
    printf("Enter your choice:");

}

int main()
{
    leadCatalog();
    for (;;)
    {
        screenmenu();
        scanf("%d", &choice);
        int choice = getIntBetween("choice",1,7);
        
        switch(choice)
        {
            case 1:
            screenFilmList();
            break;
            case 2:
            {
                int f,s;pickshow(&f,&s);screenSeatGride(f,s);
                break;
            }
            case 3:
            actionBook();
            break;
            case 4:
            actionCancel();
            break;
            case 5:
            actionFind();
            break;
            case 6:
            actionSummary();
            break;
            case 7:
            printf(CLR_TITLE"\nThank you for using our system good bye!\n"CLR_RESET);
            return 0;
        }   
    }
}
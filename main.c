#include <stdio.h>
#include <stdlib.h>
#include "meet.h"

int main() {
    load_bookings();
    
    int num;
    while (1) {
        displayMenu();
        scanf("%d", &num);
        switch (num) {
            case 1: display_menu(); break;
            case 2: add_booking(); break;
            case 3: search_booking(); break;
            case 4: update_booking(); break;
            case 5: delete_booking(); break;
            case 6: printf("Exiting.\n"); break; 
            default: printf("Invalid choice.\n");
            
        }
    } 
    
    return 0;
}
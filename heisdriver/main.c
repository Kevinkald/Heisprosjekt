#include "elev.h"
#include <stdio.h>
#include "test.h"


int main() {
    // Initialize hardware
    if (!elev_init()) {
        printf("Unable to initialize elevator hardware!\n");
        return 1;
    }
	
	int* direction_up[4]   =   { 0,0,0,0 };		//Denne legger en ener i 
	int* direction_down[4] =   { 0,0,0,0 };		//indeks 0-3 for etasje 1-4
	int* ordered_floors[4] =   { 0,0,0,0 };		//
	
	while (1) {
		checkFloorButtons(direction_up, direction_down, ordered_floors);
		printf("Direction up array\n");
		for (int i = 0; i < 4; i++) {
			printf("%d" ,*direction_up[i]);
            printf("\t");
		}
		printf("\n");
		printf("Direction down array\n");
		for (int i = 0; i < 4; i++) {
			printf("%d", *direction_down[i]);
			printf("\t");
		}
		printf("\n");
		printf("Command array\n");
		for (int i = 0; i < 4; i++) {
			printf("%d", *ordered_floors[i]);
			printf("\t");
		}
        printf("\n");
		while (!elev_get_stop_signal()) {

		}
	}
	
    
    return 0;
}

#include "elev.h"
#include <stdio.h>
#include "test.h"
#include <vector>


int main() {
    // Initialize hardware
    if (!elev_init()) {
        printf("Unable to initialize elevator hardware!\n");
        return 1;
    }
	
	//int direction_up[4] = { 0,0,0,0 };	Denne legger en ener i 
	//int direction_down[4] = { 0,0,0,0 };	indeks 0-3 for etasje 1-4
	//int ordered_floors[4] = { 0,0,0,0 };
	
	//eller

	//vector<int> ordered_up;				Denne holder etasjenr, må lage funksjoner
	//vector<int> ordered_down;				som adder og sjekker etasjene som legges til
	//vector<int> ordered_floors;
    typedef enum elevStatus { 
    idle = 0,
    goUp = 1,
    goDown = 2.
    stop = 3
} status;
    status state = idle;
    while (1) {   
        
        switch(state){
            case idle:    
                printf("Hello\n")
                break;
            
            case goUp:
                elev_set_motor_direction(DIRN_DOWN);
                                
                break;

            case goDown:
                elev_set_motor_direction(DIRN_UP);

                break;

            case stop:
                elev_set_motor_direction(DIRN_STOP);
                break;

            default:
                state = idle;

        }
    }

    return 0;
}

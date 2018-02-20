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


	//må iterate over button_channel_matrix

    int floor = 4;

    while (elev_get_stop_signal!=1) { //push stop button to continue
    	driveToFloor(floor);
    }

    printf("Press STOP button to stop elevator and exit program.\n");

    elev_set_motor_direction(DIRN_UP);

    while (1) {
        // Change direction when we reach top/bottom floor
        if (elev_get_floor_sensor_signal() == N_FLOORS - 1) {
            elev_set_motor_direction(DIRN_DOWN);
        } else if (elev_get_floor_sensor_signal() == 0) {
            elev_set_motor_direction(DIRN_UP);
        }

        // Stop elevator and exit program if the stop button is pressed
        if (elev_get_stop_signal()) {
            elev_set_motor_direction(DIRN_STOP);
            break;
        }
    }

    return 0;
}

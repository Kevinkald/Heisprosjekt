#include "elev.h"
#include <stdio.h>
#include "idle.h"


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
    


    
    status state = IDLE;
    
    while (1) {   
        
        switch(state){
            case IDLE:
                  
                state = idle();
                printf("idle\n");
                break;
            
            case UP:
                printf("going up\n");
                elev_set_motor_direction(DIRN_UP);
                if(elev_get_floor_sensor_signal() == 3){
                    state = ERROR;
                }

                break;

            case DOWN:
                printf("going down\n");
                elev_set_motor_direction(DIRN_DOWN);

                if(elev_get_floor_sensor_signal() == 0){
                    state = ERROR;
                }
                break;

            case ERROR:
                elev_set_motor_direction(DIRN_STOP);
                state = IDLE;
                printf("stop\n");
                break;

            default:
                state = IDLE;
                break;

        }
    }

    return 0;
}

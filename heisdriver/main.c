#include "elev.h"
#include <stdio.h>
<<<<<<< HEAD
#include "FSM.h"
//#include "queue.c"
=======
#include "test.h"
>>>>>>> origin


int main() {
    // Initialize hardware
    if (!elev_init()) {
        printf("Unable to initialize elevator hardware!\n");
        return 1;
    }
	
	while (1) {


        while (elev_get_stop_signal()){
            stopElevator();
            if (elev_get_floor_sensor_signal()!=-1) { 
                elev_set_door_open_lamp(1);
                timer(3);
                elev_set_door_open_lamp(0);
            }
        }
        elev_set_stop_lamp(0);


        elev_set_motor_direction(DIRN_UP);

<<<<<<< HEAD
        
=======
    while (elev_get_stop_signal()!=1) { //push stop button to continue
    	driveToFloor(floor);
    }
    if (elev_get_stop_signal()){
        stopElevator();
    }
>>>>>>> origin




    }

    


	
    
    return 0;
}
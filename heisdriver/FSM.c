#include "FSM.h"
#include "elev.h"
#include <time.h>
#include <stdio.h>
#include "queue.h"

#define N_BUTTONS 3
#define N_FLOORS 4



void timer(int N_Seconds) {

	clock_t before = clock();
	int seconds = 0;

	do {
		clock_t difference = clock() - before;
		seconds = difference / CLOCKS_PER_SEC;
	} while (seconds < N_Seconds);
}


void openDoor(void) {
	elev_set_motor_direction(DIRN_STOP);
	elev_set_door_open_lamp(1);
    timer(3);
    elev_set_door_open_lamp(0);
}


void checkStopElevator(void) {

	while (elev_get_stop_signal()){
		elev_set_motor_direction(DIRN_STOP);
		elev_set_stop_lamp(1);
		clearAll(); 								//function clears all orders
        if (elev_get_floor_sensor_signal()!=-1) { 
            openDoor();
        }
    }
    elev_set_stop_lamp(0);
}


int driveToFloor(int floor) {

	while (elev_get_floor_sensor_signal() != (floor-1)) {
		if ((floor-1) > elev_get_floor_sensor_signal()) {
			elev_set_motor_direction(DIRN_UP);
		}

		else if ((floor-1) < elev_get_floor_sensor_signal()) {
			elev_set_motor_direction(DIRN_DOWN);
		}

		while ((floor-1) != elev_get_floor_sensor_signal()) {

			printf("driving elevator towards floor\n");

		}
	}

	elev_set_motor_direction(DIRN_STOP);

	return 1;
}


void checkOutButtons(){
    for(int i = 0; i < 3; i++){
        if (elev_get_button_signal(BUTTON_CALL_UP, i)){
            setOrders(BUTTON_CALL_UP, i);
        }
        if (elev_get_button_signal(BUTTON_CALL_DOWN, i + 1)){
            setOrders(BUTTON_CALL_DOWN, i + 1);
        }
        if (elev_get_button_signal(BUTTON_COMMAND, i)){
            setOrders(BUTTON_COMMAND, i);
        }

    }
    if (elev_get_button_signal(BUTTON_COMMAND, 3)){
            setOrders(BUTTON_COMMAND, 3);
    }
}


void orderHandler(void) {

	for (int i = 0; i < 3; i++) {

		int currentFloor = elev_get_floor_sensor_signal();

			if (getOrder(BUTTON_CALL_UP,i)) {
				
				if (i > currentFloor) {
					elev_set_motor_direction(DIRN_UP);
					while (elev_get_floor_sensor_signal()!=i) {
						printf("%s\n","driving up towards floor" );
					}
					openDoor();
					clearOrder(BUTTON_CALL_UP,i);
				}

			}




		
	}

}

void updateFloorIndicator(void) {

	int currentFloor = elev_get_floor_sensor_signal();

	if (currentFloor != -1) {
		elev_set_floor_indicator(currentFloor);
	}
}
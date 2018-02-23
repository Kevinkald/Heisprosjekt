#include "FSM.h"
#include "elev.h"
#include "queue.h"
#include <time.h>
#include <stdio.h>
#include <stdlib.h>


#define N_BUTTONS 3
#define N_FLOORS 4


typedef enum tag_elev_direction { 
    IDLE = -1,
    DOWN = 0,    
    UP = 1
} state;



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

state status = IDLE;
elev_motor_direction_t motorDir;

void orderHandling(void){
	int currentFloor = elev_get_floor_sensor_signal();
	int goToFloor = -1;
	switch(status){
		case IDLE:
			for(int i = 0; i < 4; i++){
				if(getOrder(BUTTON_CALL_UP, i) == 1){
					printf("button call up \n");
					if (currentFloor > i){
						goToFloor = i;
						status = DOWN;
						break;
						
					}
					status = UP;
					break;
				}
				if(getOrder(BUTTON_CALL_DOWN, i) == 1){
					printf("button call down \n");
					status = DOWN;
					break;
				}
			}
			break;
		case DOWN:
				printf("DOWN\n");
				if(goToFloor != -1){
					elev_set_motor_direction(DIRN_DOWN);
						if (elev_get_floor_sensor_signal() == i) {
							openDoor();
							clearOrder(BUTTON_CALL_UP, i);
							clearOrder(BUTTON_COMMAND, i);
							status = UP;

				}
				for (int i = currentFloor; i >= 0; i--) {
						if (getOrder(BUTTON_CALL_DOWN, i) || getOrder(BUTTON_COMMAND, i)) {
							elev_set_motor_direction(DIRN_DOWN);
							if (elev_get_floor_sensor_signal() == i) {
								openDoor();
								clearOrder(BUTTON_CALL_DOWN, i);
								clearOrder(BUTTON_COMMAND, i);
							}

						}	
				}
				break;*/
				
		

		case UP:
				printf("UP\n");
				for (int i = currentFloor; i < 4; i++) {

						if (getOrder(BUTTON_CALL_UP, i) || getOrder(BUTTON_COMMAND, i)) {
							elev_set_motor_direction(DIRN_UP);
							if (elev_get_floor_sensor_signal() == i) {
								openDoor();
								clearOrder(BUTTON_CALL_UP, i);
								clearOrder(BUTTON_COMMAND, i);
							}

						}	
				}
				break;
	}
}




//checkout functions

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


void checkOutButtons(void){
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
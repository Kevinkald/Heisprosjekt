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
		checkOutButtons();
		checkStopElevator();
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

void orderHandling(void){
	int currentFloor = elev_get_floor_sensor_signal(); //kan bli trøbbel her når currentFloo
	switch(status){										// tar verdien -1

		case IDLE:
			for(int i = 0; i < 4; i++){
				if(getOrder(BUTTON_CALL_UP, i)){
					if (currentFloor>i) {
						status = DOWN;
					}
					else {
						printf("button call up \n");
						status = UP;
					}
					break;
				}
				else if(getOrder(BUTTON_CALL_DOWN, i)){
					printf("button call down \n");
					status = DOWN;
					break;
				}
				else if (getOrder(BUTTON_COMMAND, i)) {
					printf("Button command\n" );
					if (currentFloor>i) {
						status = DOWN;
					}
					else {
						status = UP;
					}
				}
			}
			break;

		case UP:
				printf("UP\n");
				if (currentFloor != -1) {
					for (int i = currentFloor; i < 4; i++) {
						if (getOrder(BUTTON_CALL_UP, i) || getOrder(BUTTON_COMMAND, i)) {
							elev_set_motor_direction(DIRN_UP);
							if (elev_get_floor_sensor_signal() == i) {
								openDoor();
								clearOrder(BUTTON_CALL_UP, i);
								clearOrder(BUTTON_COMMAND, i);
								clearOrder(BUTTON_CALL_DOWN,i);
							}
						}	
					}
					if (!ordersUp(currentFloor)) {
						status = DOWN;
					}
				
				}
				break;

		case DOWN:
				printf("DOWN\n");
				
				if (currentFloor != -1) {
					for (int i = currentFloor; i >= 0; i--) {
						if (getOrder(BUTTON_CALL_DOWN, i) || getOrder(BUTTON_COMMAND, i)) {
							elev_set_motor_direction(DIRN_DOWN);
							if (elev_get_floor_sensor_signal() == i) {
								openDoor();
								clearOrder(BUTTON_CALL_DOWN, i);
								clearOrder(BUTTON_COMMAND, i);
								clearOrder(BUTTON_CALL_UP, i);
							}

						}	
					}
					if (!ordersDown(currentFloor)) {
						status = IDLE;
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
            //elev_set_button_lamp(BUTTON_CALL_UP, i, getOrder(BUTTON_CALL_UP, i));
        }
        if (elev_get_button_signal(BUTTON_CALL_DOWN, i + 1)){
            setOrders(BUTTON_CALL_DOWN, i + 1);
            //elev_set_button_lamp(BUTTON_CALL_DOWN, i + 1, getOrder(BUTTON_CALL_DOWN, i + 1));
        }
        if (elev_get_button_signal(BUTTON_COMMAND, i)){
            setOrders(BUTTON_COMMAND, i);
            //elev_set_button_lamp(BUTTON_COMMAND, i, getOrder(BUTTON_COMMAND, i));
        }

    }
    if (elev_get_button_signal(BUTTON_COMMAND, 3)){
            setOrders(BUTTON_COMMAND, 3);
            //elev_set_button_lamp(BUTTON_COMMAND, 3, getOrder(BUTTON_COMMAND, 3));
    }
}

void updateFloorIndicator(void) {

	int currentFloor = elev_get_floor_sensor_signal();

	if (currentFloor != -1) {
		elev_set_floor_indicator(currentFloor);
	}
}
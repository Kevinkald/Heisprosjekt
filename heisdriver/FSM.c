#include "FSM.h"
#include "elev.h"
#include "queue.h"
#include <time.h>
#include <stdio.h>
#include <stdlib.h>


#define N_BUTTONS 3
#define N_FLOORS 4


//variable declaration
typedef enum tag_elev_direction { 
    IDLE = -1,
    DOWN = 0,    
    UP = 1
} state;

state status = IDLE;
int goToFloor = -1;


//timer function
void timer(int N_Seconds) {

	clock_t before = clock();
	int seconds = 0;

	do {
		checkOutButtons();
		stopButton();
		clock_t difference = clock() - before;
		seconds = difference / CLOCKS_PER_SEC;
	} while (seconds < N_Seconds);
}


//Finite-state-machine
void orderHandling(void){
	int currentFloor = elev_get_floor_sensor_signal();
	switch(status){
		case IDLE:
				printf("IDLE\n");
				elev_set_motor_direction(DIRN_STOP);
				for(int i = 0; i < 4; i++){
					if(getOrder(BUTTON_CALL_UP, i) || getOrder(BUTTON_COMMAND, i)){
						goToFloor = i;
						if(currentFloor > goToFloor){
							status = DOWN;
							break;
						}
						status = UP;
						break;
					}
					else if(getOrder(BUTTON_CALL_DOWN, i) || getOrder(BUTTON_COMMAND, i)){
						goToFloor = i;
						if(currentFloor < goToFloor){
							status = UP;
							break;
						}
						status = DOWN;
						break;
					}
					/*else if(getOrder(BUTTON_COMMAND, i)){ 
						goToFloor = i;
						if(currentFloor < goToFloor){
							status = UP;
							break;
						}	
						if(currentFloor > goToFloor){
							status = DOWN;
							break;
						}
					}*/
				}
				break;
				

		case UP:
				printf("UP\n");
				elev_set_motor_direction(DIRN_UP);
				updateFloorIndicator();
				if(currentFloor != -1) {
					if(goToFloor != -1){
						if(elev_get_floor_sensor_signal() == goToFloor){
							openDoor();
							clearOrder(BUTTON_COMMAND, goToFloor);
							clearOrder(BUTTON_CALL_DOWN, goToFloor);
							clearOrder(BUTTON_CALL_UP, goToFloor);
							goToFloor = -1;
							status = DOWN;
						}
					}
				
					for (int i = currentFloor; i < 4; i++) {
						if (getOrder(BUTTON_CALL_UP, i) || getOrder(BUTTON_COMMAND, i)) {
							if (elev_get_floor_sensor_signal() == i) {
								openDoor();
								clearOrder(BUTTON_CALL_DOWN, i);
								clearOrder(BUTTON_CALL_UP, i);
								clearOrder(BUTTON_COMMAND, i);
							}
						}	
					}
					if (!ordersUp(currentFloor)) {
						status = IDLE;
					}
				}
				break;

		case DOWN:
				printf("DOWN\n");
				elev_set_motor_direction(DIRN_DOWN);
				updateFloorIndicator();
				if (currentFloor != -1) {
					if(goToFloor != -1){
						if(elev_get_floor_sensor_signal() == goToFloor){
							openDoor();
							clearOrder(BUTTON_COMMAND, goToFloor);
							clearOrder(BUTTON_CALL_DOWN, goToFloor);
							clearOrder(BUTTON_CALL_UP, goToFloor);
							goToFloor = -1;
							status = UP;
						}
					}
					
					for (int i = currentFloor; i >= 0; i--) {
						if (getOrder(BUTTON_CALL_DOWN, i) || getOrder(BUTTON_COMMAND, i)) {
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
void openDoor(void) {
	elev_set_motor_direction(DIRN_STOP);
	//printf("open door\n");
	elev_set_door_open_lamp(1);
    timer(3);
    elev_set_door_open_lamp(0);

}


int stopButton(void) {

	int stopped = 0;
	while (elev_get_stop_signal()){
		elev_set_motor_direction(DIRN_STOP);
		elev_set_stop_lamp(1);
		clearAll();	
		stopped = 1;
    }
    if ((elev_get_floor_sensor_signal() != -1) && (stopped)) {
    	openDoor();
    	status = IDLE;
    }
    else if (stopped) {
    	status = IDLE;
    }
    
    elev_set_stop_lamp(0);
    return stopped;
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
        
        elev_set_button_lamp(BUTTON_CALL_UP, i, getOrder(BUTTON_CALL_UP, i));
    	elev_set_button_lamp(BUTTON_COMMAND, i, getOrder(BUTTON_COMMAND, i));
    	elev_set_button_lamp(BUTTON_CALL_DOWN, i + 1, getOrder(BUTTON_CALL_DOWN, i + 1));
    }
    
    if (elev_get_button_signal(BUTTON_COMMAND, 3)){
            setOrders(BUTTON_COMMAND, 3);
    }
    
   	elev_set_button_lamp(BUTTON_COMMAND, 3, getOrder(BUTTON_COMMAND, 3));
}


void updateFloorIndicator(void) {
	int currentFloor = elev_get_floor_sensor_signal();
	if (currentFloor != -1) {
		elev_set_floor_indicator(currentFloor);
	}
}
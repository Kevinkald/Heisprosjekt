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

state status = IDLE;
int goToFloor;
int recentFloor;

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


void openDoor(void) {
	elev_set_motor_direction(DIRN_STOP);
	elev_set_door_open_lamp(1);
    timer(3);
    elev_set_door_open_lamp(0);
}

//Finite-state-machine
void orderHandling(void){
	int currentFloor = elev_get_floor_sensor_signal();

	if (currentFloor!=-1) {
		recentFloor = currentFloor;
	}

	switch(status){
		case IDLE:
				printf("IDLE\n");
				elev_set_motor_direction(DIRN_STOP);

				if(ordersUp(recentFloor)){
						status = UP;
						break;
				}
				else if(ordersDown(recentFloor)){
						status = DOWN;
						break;
				}
				break;
				

		case UP:
				printf("UP\n");
				elev_set_motor_direction(DIRN_UP);
				updateFloorIndicator();  			//Hvorfor updateFloor.. her Jan?
				int ordersAboveFloor = 0;

				/*This for loop just checks for orders UP/COMMAND from recent visited floor,
				no exiting news here*/
				for (int i = recentFloor; i < 4; i++) {								
					if (getOrder(BUTTON_CALL_UP, i) || getOrder(BUTTON_COMMAND, i)) {
						if (currentFloor == i) {
							openDoor();
							clearOrder(i);
						}
						ordersAboveFloor = 1;
					}	
				}

				/*ordersDownAboveFloor returns 1 if there are orders-down
				above recent floor.
					Explaination of these if sentences: 
				
				First if checks if there are no up/command orders above recent floor by 
				checking that ordersAboveFloor = 0, if so ordersDownAboveFloor checks if there are any
				orders-down above recent floor. If so if stops at these floors before 
				changing to state IDLE where direction is changed to down if there are
				orders under recent floor.
				*/ 
				if (ordersDownAboveFloor(recentFloor) && (!ordersAboveFloor)) {
					for (int i = recentFloor; i < 4; i++) {
						if (getOrder(BUTTON_CALL_DOWN, i)) {
							if (currentFloor == i) {
								openDoor();
								clearOrder(i);
							}
						}
					}	
				}
				else if (!ordersAboveFloor){
					status = IDLE;
				}

				break;


		case DOWN:
				printf("DOWN\n");
				elev_set_motor_direction(DIRN_DOWN);
				updateFloorIndicator();					//hvorfor denne her?
				if (currentFloor != -1) {
					if(goToFloor != -1){
						if(elev_get_floor_sensor_signal() == goToFloor){
							openDoor();
							clearOrder(goToFloor);
							goToFloor = -1;
							status = UP;
						}
					}
					
					for (int i = currentFloor; i >= 0; i--) {
						if (getOrder(BUTTON_CALL_DOWN, i) || getOrder(BUTTON_COMMAND, i)) {
							if (elev_get_floor_sensor_signal() == i) {
								openDoor();
								clearOrder(i);
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

int stopButton(void) {

	int stopped = 0;
	
	while (elev_get_stop_signal()){
		elev_set_motor_direction(DIRN_STOP);
		elev_set_stop_lamp(1);
		clearAll();	
		checkOutButtons();
		stopped = 1;
    }

    int current_floor = elev_get_floor_sensor_signal();
    if ((current_floor != -1) && (stopped)) {
    	openDoor();
    	status = IDLE;
    }
    else if (stopped) {
    	/*if ((ordersUp(recentFloor)) && (status == UP)) {
    		status = UP;
    	}
    	else if ((ordersDown(recentFloor)) && (status == DOWN)) {
    		status = DOWN;
    	}
    	else if (ordersUp(recentFloor)) {
    		status = UP;
    	}
    	else if (ordersDown(recentFloor)) {
    		status = DOWN;
    	}
    */	status = IDLE;
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
#include "FSM.h"
#include "elev.h"
#include "queue.h"
#include "timer.h"

#include <stdio.h>
#include <stdlib.h>

//The values of the three different states
typedef enum tag_elev_direction { 
    IDLE = -1,
    DOWN = 0,    
    UP = 1
} state;

//Initializing variables
state status = IDLE;
int recent_floor;
int direction = 0;


//Finite-state-machine
void orderHandling(void){

	int current_floor = elev_get_floor_sensor_signal();

	if (current_floor!=-1) {
		recent_floor = current_floor;
	}

	switch(status){
		case IDLE:
				printf("Current state: < IDLE > \n");
				elev_set_motor_direction(DIRN_STOP);

				if(orders_up(recent_floor) || (direction == -1 && (get_order(BUTTON_CALL_UP, recent_floor) || get_order(BUTTON_CALL_DOWN, recent_floor)))){
						
						status = UP;
						break;
				}
				else if(orders_down(recent_floor) || (direction == 1 && (get_order(BUTTON_CALL_UP, recent_floor) || get_order(BUTTON_CALL_DOWN, recent_floor)))){
						
						status = DOWN;
						break;
				}
				break;
				

		case UP:
				printf("Current state: < UP > \n");
				direction = DIRN_UP;
				elev_set_motor_direction(DIRN_UP);
				update_floor_indicator();

				if(current_floor != -1) {
					for (int i = recent_floor; i < N_FLOORS; i++) {
						if (get_order(BUTTON_CALL_UP, i) || get_order(BUTTON_COMMAND, i)) {
							if (elev_get_floor_sensor_signal() == i) {
								open_door();
								clear_order(i);
							}
						}	
					}
					if (!orders_up(current_floor)) { //recent_floor her?
						status = IDLE;
					}
				}
				break;

		case DOWN:
				printf("DOWN\n");
				direction = DIRN_DOWN;
				elev_set_motor_direction(DIRN_DOWN);
				update_floor_indicator();
				if (current_floor != -1) {
					for (int i = recent_floor; i >= 0; i--) {
						if (get_order(BUTTON_CALL_DOWN, i) || get_order(BUTTON_COMMAND, i)) {
							if (elev_get_floor_sensor_signal() == i) {
								open_door();
								clear_order(i);
							}
						}	
					}
					if (!orders_down(current_floor)) { //recent_floor her?
							status = IDLE;
					}
				}
				break;		
	}
}

void open_door(void) {
    elev_set_motor_direction(DIRN_STOP);
    elev_set_door_open_lamp(1);
    timer_delay_sec(3);
    elev_set_door_open_lamp(0);
}

void check_stop_button(void) {

    int stopped = 0;

    while (elev_get_stop_signal()){
        elev_set_motor_direction(DIRN_STOP);
        elev_set_stop_lamp(1);
        clear_all();	
        check_buttons();
        stopped = 1;
    }

    int current_floor = elev_get_floor_sensor_signal();

    if ((current_floor != -1) && (stopped)) {
    	open_door();
    	status = IDLE;
    }
    else if (stopped) {
       status = IDLE;
   	}

    elev_set_stop_lamp(0);
}


void check_buttons(void){
    for(int i = 0; i < N_BUTTONS; i++){
        if (elev_get_button_signal(BUTTON_CALL_UP, i)){
            set_order(BUTTON_CALL_UP, i);            
        }
        
        if (elev_get_button_signal(BUTTON_CALL_DOWN, i + 1)){
            set_order(BUTTON_CALL_DOWN, i + 1);            
        }
        
        if (elev_get_button_signal(BUTTON_COMMAND, i)){
            set_order(BUTTON_COMMAND, i);            
        }
        
        elev_set_button_lamp(BUTTON_CALL_UP, i, get_order(BUTTON_CALL_UP, i));
    	elev_set_button_lamp(BUTTON_COMMAND, i, get_order(BUTTON_COMMAND, i));
    	elev_set_button_lamp(BUTTON_CALL_DOWN, i + 1, get_order(BUTTON_CALL_DOWN, i + 1));
    }
    
    if (elev_get_button_signal(BUTTON_COMMAND, 3)){
            set_order(BUTTON_COMMAND, 3);
    }

    elev_set_button_lamp(BUTTON_COMMAND, 3, get_order(BUTTON_COMMAND, 3));
}


void update_floor_indicator(void) {
	int current_floor = elev_get_floor_sensor_signal();
	if (current_floor != -1) {
		elev_set_floor_indicator(current_floor);
	}
}
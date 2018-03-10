#include "FSM.h"
#include "elev.h"
#include "queue.h"
#include "timer.h"

#include <stdio.h>

//The values of the three different states
typedef enum tag_elev_direction { 
    IDLE = -1,
    DOWN = 0,    
    UP = 1
} elevator_state;

//Initializing variables
elevator_state state = IDLE;
int recent_floor;
int direction = 0;

//Finite-state-machine
void elevator_controller(void){
	int current_floor = elev_get_floor_sensor_signal();

	if (current_floor != -1) {
		recent_floor = current_floor;
	}

	switch(state){
		case IDLE:
				printf("Current state: < IDLE > \n");
				elev_set_motor_direction(DIRN_STOP);

				/*This if sentence handles if elevator gets an order
				at the same floor as recent_floor.
				*/
				if ((get_order(BUTTON_CALL_UP, recent_floor) 
					|| get_order(BUTTON_CALL_DOWN, recent_floor) 
					|| get_order(BUTTON_COMMAND, recent_floor)) && current_floor != -1){
					open_door();
					clear_order(recent_floor);
					break;
				}
				else {
					check_next_state(recent_floor, direction);
				}
				break;

		case UP:
				printf("Current state: < UP > \n");
				direction = DIRN_UP;
				elev_set_motor_direction(DIRN_UP);
				update_floor_indicator();

				if (current_floor != -1) {
					for (int i = recent_floor; i < N_FLOORS; i++) {
						if (get_order(BUTTON_CALL_UP, i) || get_order(BUTTON_COMMAND, i)) {
							if (elev_get_floor_sensor_signal() == i) {
								clear_order(i);
								open_door();
							}
						}	
					}
					if (!orders_up(recent_floor)) {
						state = IDLE;
					}
				}
				break;

		case DOWN:
				printf("Current state: < DOWN > \n");
				direction = DIRN_DOWN;
				elev_set_motor_direction(DIRN_DOWN);
				update_floor_indicator();

				if (current_floor != -1) {
					for (int i = recent_floor; i >= 0; i--) {
						if (get_order(BUTTON_CALL_DOWN, i) || get_order(BUTTON_COMMAND, i)) {
							if (elev_get_floor_sensor_signal() == i) {
								clear_order(i);
								open_door();
							}
						}	
					}
					if (!orders_down(recent_floor)) {
							state = IDLE;
					}
				}
				break;		
	}
}

/*
Checks for the next state by checking if there are orders
in the same direction as the current direction of the elevator.
Handles problem with undefined floor.
*/
void check_next_state(int recent_floor, int direction) {
	if (orders_up(recent_floor)
		|| (direction == -1 && (get_order(BUTTON_CALL_UP, recent_floor)
		|| get_order(BUTTON_CALL_DOWN, recent_floor)
		|| get_order(BUTTON_COMMAND, recent_floor)))){
		state = UP;
	}
	else if (orders_down(recent_floor)
		|| (direction && (get_order(BUTTON_CALL_UP, recent_floor)
		|| get_order(BUTTON_CALL_DOWN, recent_floor)
		|| get_order(BUTTON_COMMAND, recent_floor)))){
		state = DOWN;
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

    if ((elev_get_floor_sensor_signal() != -1) && (stopped)) {
    	open_door();
    	state = IDLE;
    }
    else if (stopped) {
    	state = IDLE;
   	}

    elev_set_stop_lamp(0);
}

void check_buttons(void){
    for (int i = 0; i < N_FLOORS; i++){
        if (i < 3){ 
        	elev_set_button_lamp(BUTTON_CALL_UP, i, get_order(BUTTON_CALL_UP, i));
        	if (elev_get_button_signal(BUTTON_CALL_UP, i)){
            	set_order(BUTTON_CALL_UP, i);            
            }
            elev_set_button_lamp(BUTTON_CALL_DOWN, i + 1, get_order(BUTTON_CALL_DOWN, i + 1));
            if (elev_get_button_signal(BUTTON_CALL_DOWN, i + 1)){
            	set_order(BUTTON_CALL_DOWN, i + 1);
            }
		}
        
        elev_set_button_lamp(BUTTON_COMMAND, i, get_order(BUTTON_COMMAND, i));
        if (elev_get_button_signal(BUTTON_COMMAND, i)){
            set_order(BUTTON_COMMAND, i);            
        }	
    }
}

void update_floor_indicator(void) {
	int current_floor = elev_get_floor_sensor_signal();
	if (current_floor != -1) {
		elev_set_floor_indicator(current_floor);
	}
}
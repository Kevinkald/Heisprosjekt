#include "idle.h"
#include "elev.h"


// Number of signals and lamps on a per-floor basis (excl sensor)
#define N_BUTTONS 3
#define N_FLOORS 4



status state;

void updateLists(int direction_up[4], int direction_down[4], int ordered_floors[4]){
	for(int i = 0; i < 3; i++){
		if(elev_get_button_signal(BUTTON_CALL_UP, i) == 1){
			direction_up[i] = 1;
		}
		if(elev_get_button_signal(BUTTON_CALL_DOWN,i + 1) == 1){
			direction_down[i] = 1;
		}
		if(elev_get_button_signal(BUTTON_COMMAND,i) == 1){
			ordered_floors[i] = 1;
		}
	}
}


status idle(int direction_up[4], int direction_down[4], int ordered_floors[4]){
	for(int i = 0; i < 3; i++){
		if(elev_get_button_signal(BUTTON_CALL_UP, i) == 1){
			updateLists(direction_up, direction_down, ordered_floors);
			return UP; 
		}
		if(elev_get_button_signal(BUTTON_CALL_DOWN, i + 1) == 1){
			updateLists(direction_up, direction_down, ordered_floors);
			return DOWN;
		}
		if(elev_get_button_signal(BUTTON_COMMAND, i) == 1){
			updateLists(direction_up, direction_down, ordered_floors);
			return ERROR;
		}
	}
	return IDLE;
}


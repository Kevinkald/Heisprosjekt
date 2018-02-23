#include "idle.h"
#include "elev.h"


// Number of signals and lamps on a per-floor basis (excl sensor)
#define N_BUTTONS 3
#define N_FLOORS 4





int direction_up[4] = { 0,0,0,0 };	//Denne legger en ener i 
int direction_down[4] = { 0,0,0,0 };	//indeks 0-3 for etasje 1-4
int ordered_floors[4] = { 0,0,0,0 };

status state;

void updateLists(){
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


status idle(){
	for(int i = 0; i < 3; i++){
		if(elev_get_button_signal(BUTTON_CALL_UP, i) == 1){
			updateLists();
			return UP; 
		}
		if(elev_get_button_signal(BUTTON_CALL_DOWN, i + 1) == 1){
			updateLists();
			return DOWN;
		}
		if(elev_get_button_signal(BUTTON_COMMAND, i) == 1){
			updateLists();
			return ERROR;
		}
	}
	return IDLE;
}


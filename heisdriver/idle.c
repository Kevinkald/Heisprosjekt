#include "idle.h"
#include "elev.h"


// Number of signals and lamps on a per-floor basis (excl sensor)
#define N_BUTTONS 3

int direction_up[4] = { 0,0,0,0 };	//Denne legger en ener i 
int direction_down[4] = { 0,0,0,0 };	//indeks 0-3 for etasje 1-4
int ordered_floors[4] = { 0,0,0,0 };


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


int checkFloorButtons(){
	for(int i = 0; i < 3; i++){
		if(elev_get_button_signal(BUTTON_CALL_UP, i) == 1){
			updateLists();
			return 1;
		}
		if(elev_get_button_signal(BUTTON_CALL_DOWN, i + 1) == 1){
			updateLists();
			return 2;
		}
		if(elev_get_button_signal(BUTTON_COMMAND, i) == 1){
			updateLists();
			return 3;
		}
	}
	return 0;
}



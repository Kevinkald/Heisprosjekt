#include "idle.h"
#include "elev.h"
#include "io.h"
#include "channels.h"
#include <iostream>
#include <time.h>

// Number of signals and lamps on a per-floor basis (excl sensor)
#define N_BUTTONS 3

int direction_up[4] = { 0,0,0,0 };	//Denne legger en ener i 
int direction_down[4] = { 0,0,0,0 };	//indeks 0-3 for etasje 1-4
int ordered_floors[4] = { 0,0,0,0 };


void updateLists(){
	elev_button_type_t button;
	for(int i = 0; i < 4; i++){
		if(elev_get_button_signal(button = BUTTON_CALL_UP,i) == 1){
			direction_up[i] = 1;
		}
		if(elev_get_button_signal(button = BUTTON_CALL_DOWN,i) == 1){
			direction_down[i] = 1;
		}
		if(elev_get_button_signal(button = BUTTON_COMMAND,i) == 1){
			ordered_floors[i] = 1;
		}
	}
}


int checkFloorButtons(){
	elev_button_type_t button;
	for(int i = 0; i < 4; i++){
		if(elev_get_button_signal(button = BUTTON_CALL_UP, i) == 1){
			updateLists();
			return 0;
		}
		if(elev_get_button_signal(button = BUTTON_CALL_DOWN, i) == 1){
			updateLists();
			return 1;
		}
		if(elev_get_button_signal(button = BUTTON_COMMAND, i) == 1){
			updateLists();
			return 2;
		}
	}
}



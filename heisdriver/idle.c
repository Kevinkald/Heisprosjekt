#include "channels.h"
#include "elev.h"
#include "io.h"

#include <stdlib.h>

// Number of signals and lamps on a per-floor basis (excl sensor)
#define N_BUTTONS 3

int direction_up[4] = { 0,0,0,0 };	//Denne legger en ener i 
int direction_down[4] = { 0,0,0,0 };	//indeks 0-3 for etasje 1-4
int ordered_floors[4] = { 0,0,0,0 };


int checkFloorButtons(){
	for(int i = 0; i < 4; i++){
		if(elev_get_button_signal(0, i) == 1){
			
			return 0;
		}
		if(elev_get_button_signal(1, i) == 1){

			return 1;
		}
		if(elev_get_button_signal(2, i) == 1){

			return 2;
		}
	}
}



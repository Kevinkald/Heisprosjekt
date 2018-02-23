#include "FSM.h"
#include "elev.h"
#include <time.h>
#include <stdio.h>
//#include "queue.h"


void timer(int N_Seconds) {

	clock_t before = clock();
	int seconds = 0;

	do {
		clock_t difference = clock() - before;
		seconds = difference / CLOCKS_PER_SEC;
	} while (seconds < N_Seconds);
}

void stopElevator(void) {
	elev_set_motor_direction(DIRN_STOP);
	elev_set_stop_lamp(1);
	clearAll(); 	//function clears all orders
}


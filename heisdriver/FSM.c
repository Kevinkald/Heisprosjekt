#include "FSM.h"
#include "elev.h"
#include <time.h>
#include <stdio.h>
#include "queue.h"


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


int driveToFloor(int floor) {

	while (elev_get_floor_sensor_signal() != (floor-1)) {
		if ((floor-1) > elev_get_floor_sensor_signal()) {
			elev_set_motor_direction(DIRN_UP);
		}

		else if ((floor-1) < elev_get_floor_sensor_signal()) {
			elev_set_motor_direction(DIRN_DOWN);
		}

		while ((floor-1) != elev_get_floor_sensor_signal()) {

			printf("driving elevator towards floor\n");

		}
	}

	elev_set_motor_direction(DIRN_STOP);

	return 1;
}

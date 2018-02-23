//Floors = 1,2,3,4
//elev_get_floor_sensor_signal gives signals 0-3 for floor 1-4
#include "test.h"
#include "elev.h"
#include <time.h>

int driveToFloor(int floor) {

	while (elev_get_floor_sensor_signal() != (floor-1)) {
		if ((floor-1) > elev_get_floor_sensor_signal()) {
			elev_set_motor_direction(DIRN_UP);
		}

		else if ((floor-1) < elev_get_floor_sensor_signal()) {
			elev_set_motor_direction(DIRN_DOWN);
		}

		while ((floor-1) != elev_get_floor_sensor_signal()) {
			printf("driving elevator towards floor  ");
		}
	}

	elev_set_motor_direction(DIRN_STOP);

	return 1;
}



void checkFloorButtons(int *up[4],int *down[4], int *command[4]) {

	for (int i = 0; i < 3; i++) {

		int signalUp = elev_get_button_signal(BUTTON_CALL_UP, i);
		int signalDown = elev_get_button_signal(BUTTON_CALL_DOWN, i+1);
		int signalCommand = elev_get_button_signal(BUTTON_COMMAND, i);

		if (!(*up[i])) {
			*up[i] = signalUp;
		}
		if (!(*down[i])) {
			*down[i] = signalDown;
		}
		if (!(*command[i])) {
			*command[i] = signalCommand;
		}
	}
}



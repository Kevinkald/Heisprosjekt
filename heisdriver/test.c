//Floors = 1,2,3,4
//elev_get_floor_sensor_signal gives signals 0-3 for floor 1-4
#include "test.h"
#include "elev.h"
#include <time.h>

int driveToFloor(int floor) {

<<<<<<< HEAD
=======
	if (elev_get_floor_sensor_signal() == -1) { //-1 not defined floor
		elev_set_motor_direction(DIRN_DOWN);
		while (elev_get_floor_sensor_signal() == -1) {
			printf("driving down\n");
		}
		elev_set_motor_direction(DIRN_UP); //effective stopping motor
		elev_set_motor_direction(DIRN_STOP);
	}

>>>>>>> origin
	while (elev_get_floor_sensor_signal() != (floor-1)) {
		if ((floor-1) > elev_get_floor_sensor_signal()) {
			elev_set_motor_direction(DIRN_UP);
		}

		else if ((floor-1) < elev_get_floor_sensor_signal()) {
			elev_set_motor_direction(DIRN_DOWN);
		}

		while ((floor-1) != elev_get_floor_sensor_signal()) {
<<<<<<< HEAD
			printf("driving elevator towards floor  ");
=======
			printf("driving elevator towards floor\n");
>>>>>>> origin
		}
	}

	elev_set_motor_direction(DIRN_STOP);

	return 1;
}

<<<<<<< HEAD


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
=======
void stopElevator(void) {
	elev_set_motor_direction(DIRN_STOP);
	elev_set_stop_lamp(1);

	if (elev_get_floor_sensor_signal()!=-1) { 
		elev_set_door_open_lamp(1);
		int clock_speed = CLOCKS_PER_SEC;
		int totalClocks = clock_speed*3;
		int count = 0;
		while (count < totalClocks) {
			count++;
>>>>>>> origin
		}
	}
}

<<<<<<< HEAD

=======
//void updateOrders(void) {
//	for (int i = 0; i < N_BUTTONS) {
//		for (int j = 0; j < N_FLOORS) {
//			if (button_channel_matrix[i][j])
//		}
//	}
//
>>>>>>> origin

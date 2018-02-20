//Floors = 1,2,3,4
//elev_get_floor_sensor_signal gives signals 0-3 for floor 1-4
#include "test.h"
#include "elev.h"

int driveToFloor(int floor) {

	if (elev_get_floor_sensor_signal() == -1) { //-1 not defined floor
		elev_set_motor_direction(DIRN_DOWN);
		while (elev_get_floor_sensor_signal() == -1) {
			printf("driving down");
		}
		elev_set_motor_direction(DIRN_UP); //effective stopping motor
		elev_set_motor_direction(DIRN_STOP);
	}

	while (elev_get_floor_sensor_signal() != (floor-1)) {
		if ((floor-1) > elev_get_floor_sensor_signal()) {
			elev_set_motor_direction(DIRN_UP);
		}

		else if ((floor-1) < elev_get_floor_sensor_signal()) {
			elev_set_motor_direction(DIRN_DOWN);
		}

		while ((floor-1) != elev_get_floor_sensor_signal()) {
			printf("driving elevator towards floor");
		}
	}

	elev_set_motor_direction(DIRN_STOP);

	return 1;
}

void stopElevator(void) {
	elev_set_motor_direction(DIRN_STOP);
	elev_set_stop_lamp(1);

	if (elev_get_floor_sensor_signal()!=-1) {
		//open door by turning on door open light.
		// for 3 sek
		//then close
		elev_set_door_open_lamp(1);
		int clock_speed = CLOCKS_PER_SEC;
		int count;
		while (count < (clock_speed * 3)) {
			count++;
		}
		elev_set_door_open_lamp(0);
	}
}


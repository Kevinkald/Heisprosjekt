//Floors = 1,2,3,4
//elev_get_floor_sensor_signal gives signals 0-3 for floor 1-4
bool driveToFloor(int floor) {

	if (elev_get_floor_sensor_signal() == -1) { //-1 not defined floor
		elev_set_motor_direction(DIRN_DOWN);
		while (elev_get_floor_sensor_signal() == -1) {
			printf("driving down");
		}
		elev_set_motor_direction(DIRN_UP); //effective stopping motor
		elev_set_motor_direction(DIRN_STOP);
	}

	while (elev_get_floor_sensor_signal() != (floor-1) {
		if (floor > (elev_get_floor_sensor_signal()+1)) {
			elev_set_motor_direction(DIRN_UP);
		}

		else if (floor < (elev_get_floor_sensor_signal() + 1)) {
			elev_set_motor_direction(DIRN_DOWN);
		}

		while (floor != (elev_get_floor_sensor_signal() + 1)) {
			printf("driving elevator towards floor");
		}

	}

	elev_set_motor_direction(DIRN_STOP);

	return true;
}
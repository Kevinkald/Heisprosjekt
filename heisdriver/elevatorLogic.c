int driveToFloor(int floor) {

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
		elev_set_door_open_lamp(1);
		waitNSeconds(3);
		elev_set_door_open_lamp(0);
	}
}
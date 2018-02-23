#pragma once
#include "elev.h"
#include "io.h"
#include "channels.h"
#include <time.h>

int driveToFloor(int floor);

void stopElevator(void);

void updateOrders(void);
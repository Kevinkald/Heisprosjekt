#pragma once
#include "elev.h"
#include "io.h"
#include "channels.h"
#include <iostream>
#include <time.h>

int driveToFloor(int floor);

void stopElevator(void);

void updateOrders(void);

void checkFloorButtons(int up[4], int down[4], int command[4]);
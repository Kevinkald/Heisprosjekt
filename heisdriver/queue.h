#pragma once
#include "elev.h"

void setOrders(elev_button_type_t orderButton, int floor);
int getOrder(elev_button_type_t orderButton, int floor );
void clearOrder(elev_button_type_t orderButton, int floor);

//function clears all elevator orders
void clearAll(void);

//prints elevator order matrix 
void printmatrix(void);

//returns 1 if there are orders up from current floor
int ordersUp(int currentFloor);

//returns 1 if there are orders down from current floor
int ordersDown(int currentFloor);


#pragma once
#include "elev.h"

#define N_BUTTONS 3
#define N_FLOORS 4



/**
  Initialize elevator.
  @return Non-zero on success, 0 on failure.
*/
void setOrders(elev_button_type_t orderButton, int floor);



/**
  Initialize elevator.
  @return Non-zero on success, 0 on failure.
*/
int getOrder(elev_button_type_t orderButton, int floor );



/**
  Initialize elevator.
  @return Non-zero on success, 0 on failure.
*/
void clearOrder(int floor);



/**
  Clears all orders.
  @return Non-zero on success, 0 on failure.
*/
void clearAll(void);



/**
  Initialize elevator.
  @return Non-zero on success, 0 on failure.
*/
void printmatrix(void);



/**
  Checks if there are orders above recent floor.
  @return Non-zero on success, 0 on failure.
*/
int ordersUp(int currentFloor);



/**
  Checks if there are orders under recent floor.
  @return Non-zero on success, 0 on failure.
*/
int ordersDown(int currentFloor);
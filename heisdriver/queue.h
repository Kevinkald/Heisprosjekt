#ifndef __QUEUE_H__
#define __QUEUE_H__

#include "elev.h"

#define N_BUTTONS 3
#define N_FLOORS 4



/**
  Sets an order for the given button and floor in the order matrix.
  @param button Which button type to check. Can be BUTTON_CALL_UP,
    BUTTON_CALL_DOWN or BUTTON_COMMAND (button "inside the elevator).
  @param floor Which floor to check button. Must be 0-3.
*/
void set_order(elev_button_type_t button, int floor);



/**
  Checks the order matrix for a specific order.
  @param button Which button type to check. Can be BUTTON_CALL_UP,
    BUTTON_CALL_DOWN or BUTTON_COMMAND (button "inside the elevator).
  @param floor Which floor to check button. Must be 0-3.
  @return 1 if the button is requested at the given floor, 0 otherwise.
*/
int get_order(elev_button_type_t button, int floor);



/**
  Clears orders for a specific floor.
  @param floor Which floor to check button. Must be 0-3.
*/
void clear_order(int floor);



/**
  Clears all orders from order matrix.
*/
void clear_all(void);



/**
  Checks if there are orders above recent floor.
  @param recent_floor last floor visited.
  @return 1 if there are orders above recent visited floor, 0 otherwise.
*/
int orders_up(int recent_floor);



/**
  Checks if there are orders under recent floor.
  @param recent_floor last floor visited.
  @returns 1 if there are orders under recent visited floor, 0 otherwise.
*/
int orders_down(int recent_floor);



/**
  Prints the order matrix.
*/
void print_order_matrix(void);

#endif // #ifndef __QUEUE_H__
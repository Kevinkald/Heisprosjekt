#pragma once

#define N_BUTTONS 3
#define N_FLOORS 4



/**
  Sets an order for the given button and floor in the order matrix.
*/
void set_order(elev_button_type_t button_type, int floor);



/**
  Checks the order matrix for a specific order.
  @return 1 if the button is requested at the given floor, 0 otherwise.
*/
int get_order(elev_button_type_t button_type, int floor);



/**
  Clears orders for a specific floor.
*/
void clear_order(int floor);



/**
  Clears all orders from order matrix.
*/
void clear_all(void);



/**
  Prints the order matrix.
*/
void print_order_matrix(void);



/**
  Checks if there are orders above recent floor.
  @return 1 if there are orders above recent visited floor, 0 otherwise.
*/
int orders_up(int recent_floor);



/**
  Checks if there are orders under recent floor.
  @returns 1 if there are orders under recent visited floor, 0 otherwise.
*/
int orders_down(int recent_floor);
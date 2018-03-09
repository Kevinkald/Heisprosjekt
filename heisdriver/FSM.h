#pragma once


/**
  Checks if the elevator buttons are pushed and updates the order matrix.
*/
void check_buttons(void);



/**
  Stops the elevator, manages the door-open light and lasts 3 seconds.
*/
void open_door(void);



/**
  Checks if the stop button is pushed. If pushed the elevator stops,
  stop lamp is lits up, all orders are cleared. If elevator is in a defined
  floor the door opens for 3 seconds, and elevator goes to IDLE state.
*/
void check_stop_button(void);



/**
  Checks the order matrix for a specific order.
*/
void orderHandling(void);



/**
  Checks the order matrix for a specific order.
  @return 1 if the button is requested at the given floor, 0 otherwise.
*/
void update_floor_indicator(void);
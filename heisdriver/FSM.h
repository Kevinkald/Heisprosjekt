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
  Handles the transitions between the states IDLE, UP and DOWN
  by handling the order matrix.
*/
void elevator_controller(void);



/**
  Updates the floor indicator when a new floor is visited.
*/
void update_floor_indicator(void);
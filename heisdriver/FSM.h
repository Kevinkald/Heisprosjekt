#ifndef __FSM_H__
#define __FSM_H__


#include "elev.h"

/**
  Handles the transitions between the states IDLE, UP and DOWN
  by handling the order matrix.
*/
void elevator_controller(void);



/**
  Checks the next state by checking if there are orders in same
  direction above recent visited floor, if not it checks if there
  are orders in same direction under the recent visited floor.
  Handles if stop button is pushed and elevator is in non
  defined floor.
  @param recent_floor last floor visited.
  @param direction, direction of the elevator -1 for down 1 for up. 
*/
void check_next_state(int recent_floor, int direction);



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
  Checks if the elevator buttons are pushed and updates the order matrix.
*/
void check_buttons();



/**
  Updates the floor indicator when a new floor is visited.
*/
void update_floor_indicator(void);


#endif // #ifndef __FSM_H___
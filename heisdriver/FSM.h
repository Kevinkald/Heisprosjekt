#pragma once



/**
  Delays the elevator for n_sec seconds.
*/
void timer_delay_sec(int n_sec);



/**
  Checks 
  @return 1 if the button is requested at the given floor, 0 otherwise.
*/
void check_buttons(void);



/**
  Checks the order matrix for a specific order.
  @return 1 if the button is requested at the given floor, 0 otherwise.
*/
void open_door(void);



/**
  Checks the order matrix for a specific order.
  @return 1 if the button is requested at the given floor, 0 otherwise.
*/
void check_stop_button(void);



/**
  Checks the order matrix for a specific order.
  @return 1 if the button is requested at the given floor, 0 otherwise.
*/
void orderHandling(void);



/**
  Checks the order matrix for a specific order.
  @return 1 if the button is requested at the given floor, 0 otherwise.
*/
void update_floor_indicator(void);
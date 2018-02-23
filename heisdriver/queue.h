#pragma once

#include "elev.h"

void setOrders(elev_button_type_t orderButton, int floor);
int getOrder(elev_button_type_t orderButton, int floor );
void clearOrder(elev_button_type_t orderButton, int floor);
void clearAll(void);
void printmatrix(void);
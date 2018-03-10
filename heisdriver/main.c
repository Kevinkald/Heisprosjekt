#include "elev.h"
#include "FSM.h"
#include "queue.h"

#include <stdio.h>


int main() {
    // Initialize hardware
    if (!elev_init()) {
        printf("Unable to initialize elevator hardware!\n");
        return 1;
    }

	printf("started program");

	while (1) {	
        check_stop_button();
        elevator_controller();
        update_floor_indicator();
        check_buttons();
        print_order_matrix();
    }
    return 0;
}
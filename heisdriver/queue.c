#include "queue.h"
#include "elev.h"

#include <stdio.h>


// Orders up in first row, orders down second row, commands third row.
int order_matrix[N_BUTTONS][N_FLOORS] = {
	{ 0,0,0,0 },  
	{ 0,0,0,0 },  
    { 0,0,0,0 }   
};

void set_order(elev_button_type_t button, int floor){
	for (int i = 0; i < N_BUTTONS; i++){
		for (int j = 0; j < N_FLOORS; j++){
			if (button == i){
				if (floor == j){
					order_matrix[i][j] = 1;
				}
			}
		}
	}
}

int get_order(elev_button_type_t button, int floor){
	return order_matrix[button][floor];
}

void clear_order(int floor){
	order_matrix[0][floor] = 0;
	order_matrix[1][floor] = 0;
	order_matrix[2][floor] = 0;
}

void clear_all(){
	for (int i = 0; i < N_BUTTONS; i++){
		for (int j = 0; j < N_FLOORS; j++){
			order_matrix[i][j] = 0;
		}
	}
}

int orders_up(int recent_floor) {
	for (int i = recent_floor + 1; i < N_FLOORS; i++) {
		if (get_order(BUTTON_CALL_UP, i) || get_order(BUTTON_COMMAND, i) || get_order(BUTTON_CALL_DOWN, i)) {
			return 1;
		}
	}
	return 0;
}

int orders_down(int recent_floor) {
	for (int i = recent_floor - 1; i >= 0; i--) {
		if (get_order(BUTTON_CALL_DOWN, i) || get_order(BUTTON_COMMAND, i) || get_order(BUTTON_CALL_UP, i)) {
			return 1;
		}
	}
	return 0;
}

void print_order_matrix(){
	for (int i = 0; i < N_BUTTONS; i++){
		for (int j = 0; j < N_FLOORS; j++){
			printf("%d" , order_matrix[i][j]);
		}
		printf("\n");
	}
	printf("\n");
}
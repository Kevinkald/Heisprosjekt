#include "queue.h"
#include "channels.h"
#include "io.h"
#include <stdlib.h>
#include <stdio.h>


int matrixOrderList[N_BUTTONS][N_FLOORS] = {
	{ 0,0,0,0 },  //order list direction UP 1 - 3 floor
	{ 0,0,0,0 },  //order list direction DOWN 2 - 3 floor
    { 0,0,0,0 }   //Request button 1 - 4 floor
};

void setOrders(elev_button_type_t orderButton, int floor){
	for(int i = 0; i < N_BUTTONS; i++){
		for(int j = 0; j < 4; j++){
			if((int)orderButton == i){
				if(floor == j){
					matrixOrderList[i][j] = 1;
				}
			}
		}
	}
}

int getOrder(elev_button_type_t orderButton, int floor ){

	return matrixOrderList[(int)orderButton][floor];
}

void clearOrder(int floor){
	matrixOrderList[0][floor] = 0;
	matrixOrderList[1][floor] = 0;
	matrixOrderList[2][floor] = 0;
}

void clearAll(){
	for(int i = 0; i < N_BUTTONS; i++){
		for(int j = 0; j < N_FLOORS; j++){
			matrixOrderList[i][j] = 0;
		}
	}
}

void printmatrix(){
	for(int i = 0; i < N_BUTTONS; i++){
		for(int j = 0; j < N_FLOORS; j++){
			printf("%d" , matrixOrderList[i][j]);
		}
		printf("\n");
	}
	printf("\n");
}

int ordersUp(int currentFloor) {
	for (int i = currentFloor + 1; i < N_FLOORS; i++) {
		if (getOrder(BUTTON_CALL_UP, i) || getOrder(BUTTON_COMMAND, i) || getOrder(BUTTON_CALL_DOWN, i)) {
			return 1;
		}
	}
	return 0;
}

int ordersDown(int currentFloor) {
	for (int i = currentFloor - 1; i >= 0; i--) {
		if (getOrder(BUTTON_CALL_DOWN, i) || getOrder(BUTTON_COMMAND, i) || getOrder(BUTTON_CALL_UP, i)) {
			return 1;
		}
	}
	return 0;
}
#include "queue.h"
#include "channels.h"
#include "elev.h"
#include "io.h"

#include <stdlib.h>




int matrixOrderList[3][4] = {
	{ 0,0,0,0 },  //order list direction up 
	{ 0,0,0,0 },  //order list direction down
    { 0,0,0,0 }   //Request button 
}
    

void setOrders(elev_button_type_t orderButton, int floor){
	for(int i = 0; i < 3; i++){
		for(int j = 0; j < 4; j++){
			if(int(orderButton) == i){
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

void clearOrder(elev_button_type_t orderButton, int floor){
	if ((int)orderButton == 0){
		matrixOrderList[0][floor] = 0;
	}
	if ((int)orderButton == 1){
		matrixOrderList[1][floor] = 0;
	}
	if ((int)orderButton == 2){
		matrixOrderList[2][floor] = 0;
	}

}

void clearAll(){
	for(int i = 0; i < 3; i++){
		for(int j = 0; j < 4; j++){
			if(int(orderButton) == i){
				if(floor == j){
					matrixOrderList[i][j] = 0;
				}
			}
		}
	}
}


void printmatrix(){
	for(int i = 0; i < 3; i++){
		for (int j = 0; i < 4; j++){
			printf("%d" , matrixOrderList[i][j]);
		}
		printf("/n");
	}
}

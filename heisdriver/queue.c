#include "queue.h"
#include "channels.h"
#include "io.h"

#include <stdlib.h>
#include <stdio.h>




int matrixOrderList[3][4] = {
	{ 0,0,0,0 },  //order list direction UP 1 - 3 floor
	{ 0,0,0,0 },  //order list direction DOWN 2 - 3 floor
    { 0,0,0,0 }   //Request button 1 - 4 floor
<<<<<<< HEAD
};

||||||| merged common ancestors

=======
};
>>>>>>> f302d77876d799a21ac55dc78152c03f59c06215



void setOrders(elev_button_type_t orderButton, int floor){
	for(int i = 0; i < 3; i++){
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
			matrixOrderList[i][j] = 0;
		}
	}
}


void printmatrix(){
	for(int i = 0; i < 3; i++){
		for (int j = 0; j < 4; j++){
			printf("%d" , matrixOrderList[i][j]);
		}
		printf("\n");
	}
	printf("\n");
}


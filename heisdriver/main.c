#include "elev.h"
#include <stdio.h>
#include "idle.h"


int main() {
    // Initialize hardware
    if (!elev_init()) {
        printf("Unable to initialize elevator hardware!\n");
        return 1;
    }
	

    while(1){
        printf("Hello");
    }





    return 0;
}

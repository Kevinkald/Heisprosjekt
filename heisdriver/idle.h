#pragma once
#include "io.h"
#include "channels.h"
#include <time.h>

// Number of floors
#define N_FLOORS 4

typedef enum elevStatus { 
    IDLE = 0,
    UP = 1,
    DOWN = 2,
    ERROR = 3
} status;


void updateLists(void);
status idle(void);


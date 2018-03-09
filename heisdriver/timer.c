#include "timer.h"
#include "FSM.h" //Hmmm, burde timeren ha tilgang til FSM, burde det ikke være omvendt?

void timer_delay_sec(int n_sec) {

	clock_t before = clock();
	int seconds = 0;

	do {
		check_buttons();
		check_stop_button();
		clock_t difference = clock() - before;
		seconds = difference / CLOCKS_PER_SEC;
	} while (seconds < n_sec);
}

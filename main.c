#include <stdio.h>

int main(){
	
	printf("(Press key to continue: )\n");
	char c;
	char k = 'k';
	c=getchar( );
	printf("you entered:\n");
	putchar(c);
	printf(" \n");

	while(c!=k) {
		printf("press k to stop!!\n");
		c=getchar( );
	}
	printf("Program done, terminating program.\n");
	return 0;
}
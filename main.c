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
	printf("Hello Kevin\n");
	printf("This is Jan <3\n");
	printf(" \n");
	printf("Pull this program Jan\n");
	printf(" \n");
	printf("Program done, terminating program.\n");
	return 0;
}

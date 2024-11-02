#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <time.h>

int main(){
	int input;
	srand(time(NULL));
	int secret = rand();
	printf("Ender a number:\n");
	scanf("%d",&input);

	if (input == secret){
		printf("Correct!\n");
	}
	return 0;
}

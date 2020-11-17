/*
The inner workings of the game. Simple as.

*/
#include <stdio.h>
#define numberOfDebounce 3
#define maxScore 5

//This is a prototyping file with functions needed for game logic.
int softwareDebounce = 0;
int score = 0;

int checkifIRBreaks(int IRValue, int IRThreshold) {
	if (IRValue > IRThreshold) {
		softwareDebounce++;
		printf("We have registered a score, but will check up to %d times, now %d \n", numberOfDebounce, softwareDebounce);
		if (softwareDebounce >= numberOfDebounce) {
			softwareDebounce = 0;
			return 0;
			
		}
	}
	else {
		printf("nothing");
		return 1;
		softwareDebounce = 0;
	}
}

int checkIfAlive(int maxScoreVariable, int IRValue, int IRThreshold) {
	for (;;) {
		while (score < maxScoreVariable) {
			while (checkifIRBreaks(2,1)) {
			}
			score++;
			oled_print("You have scored, and have %d points: \n", score);
			if (score >= maxScoreVariable) {
				oled_print("You have won, thanks for playing with us :-)!");
				return 1;
			}
		}
	}
	return 0;
}

void main() {
	while(checkIfAlive(maxScore)) {}
}

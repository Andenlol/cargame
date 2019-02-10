/* menu.c
 * Created 2018-02-28
 * by Alexander Nordström
 *
 * Different menus
 */

#include <pic32mx.h>
#include <stdint.h>
#include "gameHeader.h"

int getbtns (void){
	int btns = PORTD & 0x0e0;
	btns = btns >> 5;
	return btns;
}

void mainMenu(void) {
	int firstLoop = 1;
	while (1) {
		if (firstLoop) {
			delay(1000000);
			firstLoop = 0;
		}
		display_string(0, "Car Game");
		display_string(1, "1. Start");
		display_string(2, "2. Rules");
		display_string(3, "");
		display_update();
		if (((getbtns() & 0x04) != 0) && !firstLoop) {
			chooselevel();
			firstLoop = 1;
		}
		if(((getbtns() & 0x02) != 0) && !firstLoop) {
			ruleMenu();
			firstLoop = 1;
		}
	}		
}

int chooselevel(void){
	int firstLoop = 1;
	while(1) {
		if (firstLoop) {
			delay(1000000);
			firstLoop = 0;
		}
		display_string(0, "1. City");
		display_string(1, "2. Forest");
		display_string(2, "3. Ocean");
		display_string(3, "");
		display_update();
		if(((getbtns() & 0x04) != 0) && !firstLoop){
			if (difficultyMenu(0) == 0) {
				return 0;
			} 
			else {
				firstLoop = 1;
			}
		}
		
		if(((getbtns() & 0x02) != 0) && !firstLoop){
			if (difficultyMenu(1) == 0) {
				return 0;
			} 
			else {
				firstLoop = 1;
			}
		}
		
		if(((getbtns() & 0x01) != 0) && !firstLoop){
			if (difficultyMenu(2) == 0) {
				return 0;
			} 
			else {
				firstLoop = 1;
			}
		}
	}
}

	
int difficultyMenu(int level) {
	int firstLoop = 1;
	unsigned int volt;
	int difficulty = 0;
	int gameReturn = 0;
	while (1) {
		if (firstLoop) {
			delay(1000000);
			firstLoop = 0;
		}
		
		AD1CON1 |= (0x1 << 1);
		while(!(AD1CON1 & (0x1 << 1)));
		while(!(AD1CON1 & 0x1));
	
		/* Get the analog value */
		volt = ADC1BUF0;
		
		difficulty = volt / 32 / 3.2;
	
		display_string(0, "Choose Difficulty");
		display_string(1, "1. Start Game");
		display_string(2, "2. Quit");
		
		if (difficulty == 0) {
			display_string(3, "Difficulty = 0");
		}
		else if (difficulty == 1) {
			display_string(3, "Difficulty = 1");
		}
		else if (difficulty == 2) {
			display_string(3, "Difficulty = 2");
		}
		else if (difficulty == 3) {
			display_string(3, "Difficulty = 3");
		}
		else if (difficulty == 4) {
			display_string(3, "Difficulty = 4");
		}
		else if (difficulty == 5) {
			display_string(3, "Difficulty = 5");
		}
		else if (difficulty == 6) {
			display_string(3, "Difficulty = 6");
		}
		else if (difficulty == 7) {
			display_string(3, "Difficulty = 7");
		}
		else if (difficulty == 8) {
			display_string(3, "Difficulty = 8");
		}
		else if (difficulty == 9) {
			display_string(3, "Difficulty = 9");
		}
		
		display_update();
		if(((getbtns() & 0x02) != 0) && !firstLoop) {
			return 0; // Main menu
		}

		if (((getbtns() & 0x04) != 0) && !firstLoop) {
			// Game starts
			gameReturn = game(level, difficulty);
			if (gameReturn == 0) {
				if (LostMenu() == 0) {
					return 0; // Main menu
				}
				else {
					return 1; // Level select
				}
			} 
			else if (gameReturn == 1) {
				return 0; // Main menu
			}
			else if (gameReturn == 2) {
				if (winMenu() == 0) {
					return 0; // Main menu
				}
				else {
					return 1; // Level select
				}
			}
		}
		
	}		
}

int PauseMenu(void){
	delay(1000000);
	while(1) {
		display_string(0, "Pause");
		display_string(1, "1. Continue");
		display_string(2, "2. Quit");
		display_string(3, "");
		display_update();
		if(((getbtns() & 0x04) != 0)) {
			return 1;
		}
		if(((getbtns() & 0x02) != 0)) {
			return 0;
		}
	}
}

int winMenu(void){
	delay(1000000);
	while(1) {
		display_string(0, "Congratulations");
		display_string(1, "You win!");
		display_string(2, "1. Play again");
		display_string(3, "2. Main Menu");
		display_update();
		if(((getbtns() & 0x02) != 0)) {
			return 0;
		}
		if(((getbtns() & 0x04) != 0)) {
			return 1;
		}
	}
}

int LostMenu(void){
	delay(1000000);
	while(1) {
		display_string(0, "You Lose");
		display_string(1, "1. Try again");
		display_string(2, "2. Quit");
		display_string(3, "");
		display_update();
		if(((getbtns() & 0x04) != 0)) {
			return 1;
		}
		if(((getbtns() & 0x02) != 0)) {
			return 0;
		}	
	}
}	

int ruleMenu(void){
	delay(1000000);
	while(1) {
		display_string(0, "Controls");
		display_string(1, "Steer with wheel");
		display_string(2, "BT4 up, BT3 down");
		display_string(3, "Don't get hit");
		display_update();
		if(((getbtns() & 0x04) != 0)) {
			return 0;
		}
	}
}	



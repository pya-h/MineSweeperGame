#include <iostream>
#include <string>
#include <conio.h>
// now include the header designed for the game
#include "minesweeper.h"

using namespace std;


int main() {
	MineSweeperGame game(16, 30);
	// resize the console so it can contain the table of the sepcified dimensions
	game.resizeConsole();
	//cout << table.getDimensions();
	// draw the table of the game, based on the parameters sent for MineSweeperGame class
	game.draw();
	game.pause();
	bool isGameOver = false;
	// game starts here:
	while(!isGameOver) {
		const char movement = _getch();
		switch(movement) {
			case 'd':
				
				break;
		}
	}
	/*
	drawTable();
	int a ;
	cin >> a;
	*/
	return 0;
}
#include <iostream>
#include <string>
#include <conio.h>
// now include the header designed for the game
#include "minesweeper.h"

using namespace std;


int main() {
	Player player;
	MineSweeperGame game(player, 11, 26);
	// resize the console so it can contain the table of the sepcified dimensions
	game.resizeConsole();
	//cout << table.getDimensions();
	// draw the table of the game, based on the parameters sent for MineSweeperGame class
	game.draw();
	//game.pause();
	bool isGameOver = false;
	// TODO: Checkout memory alloc/deallocations
	while(!isGameOver) {
		const char movement = _getch();
		if (!game.isMessageBoxEmpty()) {
			game.clearMessageBox();
		}
		if (!player.startedAt) {
			player.start();
		}
		system("color 70");
		switch(movement) {
			case 'd':
				// move right
				game.dispositionCursor(0, +1);
				break;
				
			case 'a':
				// move left
				game.dispositionCursor(0, -1);
				break;
				
			case 'w':
				// move up
				game.dispositionCursor(-1, 0);
				break;
				
			case 's':
				// move down
				game.dispositionCursor(+1, 0);
				break;
			case '\r':
				game.openCurrentBlock();
				break;
			default:
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
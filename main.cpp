#include <iostream>
#include <string>
#include <conio.h>
#include "minesweeper.h"

using namespace std;


int main() {
	bool likeToPlay = true;
	while (likeToPlay) {
		MineSweeperGame *game = new MineSweeperGame(new Player(), 11, 26);
		// resize the console so it can contain the table of the sepcified dimensions
		game->resizeConsole();
		//cout << table.getDimensions();
		// draw the table of the game, based on the parameters sent for MineSweeperGame class
		game->draw();
		//game.pause();
		bool isGameOver = false;
		// TODO: Checkout memory alloc/deallocations
		while (!isGameOver) {
			const char movement = _getch();
			if (!game->isMessageBoxEmpty()) {
				game->clearMessageBox();
			}
			if (!game->getPlayer().startedAt) {
				game->getPlayer().start();
				game->showPlayerPoint();
			}
			game->defaultColoring();
			switch (movement) {
			case 'd':
			case 'D':
				// move right
				game->dispositionCursor(0, +1);
				break;
			case 'a':
			case 'A':
				// move left
				game->dispositionCursor(0, -1);
				break;
			case 'w':
			case 'W':
				// move up
				game->dispositionCursor(-1, 0);
				break;
			case 's':
			case 'S':
				// move down
				game->dispositionCursor(+1, 0);
				break;
			case '\r':
				isGameOver = game->openCurrentBlock();
				break;
			default:
				break;
			}
		}

		game->showMessage("You Lose! Wanna Restart? (Y = Yes, O.W = No)", "ERROR", false);
		
		likeToPlay = tolower(_getch()) == 'y';
		game->clearMessageBox(); 
		// TODO: Improve game over: 1- Create player record history 2- Better UI 
		delete game;
		system("cls"); // FIXME: Use OS-independent code for clear screen
	}
	return 0;
}
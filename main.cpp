#include <iostream>
#include <string>
#include "minesweeper.h"

using namespace std;

void setConsoleSize(int width, int height) {

}


int main() {
	MineSweeperGame game(16, 30);
	game.resizeConsole();
	//cout << table.getDimensions();
	game.draw();
	game.pause();
	/*
	drawTable();
	int a ;
	cin >> a;
	*/
	return 0;
}
#include "minesweeper.h"

using namespace std;
void MineSweeperGame::resizeConsole() {
	COORD coord;
	const int width = this->columns * HORIZONTAL_SCALE, height = this->rows * VERTICAL_SCALE;
    coord.X = width;
    coord.Y = height;
    SMALL_RECT rect;
    rect.Left = 0;
    rect.Top = 0;
    rect.Right = width - 1;
    rect.Bottom = height - 1;
    SetConsoleScreenBufferSize(GetStdHandle(STD_OUTPUT_HANDLE), coord);
    SetConsoleWindowInfo(GetStdHandle(STD_OUTPUT_HANDLE), TRUE, &rect);
}

MineSweeperGame::~MineSweeperGame() {
	// TODO: call gameOver method
	//cout << "Game Over";
}

string MineSweeperGame::getDimensions() {
	return to_string(this->rows) + " x " + to_string(this->columns);
}

void MineSweeperGame::moveTo(short int x, short int y) {
    COORD coord;
    coord.X = x;
    coord.Y = y;
    SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), coord);
}

void MineSweeperGame::draw() {
	int i,j;
   /*for(i = 0;i < mty;i++)
   	for(j = 0;j > mtx;j++)
      	t[ty][tx] = NULL;*/
	cout << endl << endl << endl << endl;
	for(i = 0; i <= this->rows;i++)
	{
		cout << "\t\t";
		for(j = 0;j < this->columns;j++)
			cout << " --";
		//cout << ".";
		cout << endl;
		cout << "\t\t";
		for(j = 0;j <= this->columns;j++)
			cout << "|  ";
		cout << endl;
	}
	cout << "\t\t";
	for(j = 0;j < this->columns;j++)
		cout << " --";
}
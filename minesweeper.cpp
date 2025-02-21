#include "minesweeper.h"
#include <windows.h>
#include <stdlib.h>
#include <iostream>
#include "utils.h"

using namespace std;

void MineSweeperGame::pause() {
	std::cout << std::endl;
	system("pause");	
}

void MineSweeperGame::resizeConsole() {
	// FIXME: Seems not working on windows 11

	// use windows.h library to resize the console into the desired width and heights
	COORD coord;
	const int width = this->columns * HORIZONTAL_SCALE, height = this->rows * VERTICAL_SCALE;
    // set the position and the coordinates of the console on the windows
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
	// Class destructor
	// TODO: call gameOver method
	//cout << "Game Over";
}

string MineSweeperGame::getDimensions() {
	// just used to inform about the dimensions used in the object.
	return to_string(this->rows) + " x " + to_string(this->columns);
}

void MineSweeperGame::moveTo(uint8_t y, uint8_t x) {
	// transfer the text cursor of the console to a target destination
	// used for directional player move
	gotoxy(x, y);
	this->cursor->update(y, x, this->northY, this->westX);
}

void MineSweeperGame::moveTo(uint8_t y, uint8_t x, uint8_t row, uint8_t column) {
	// transfer the text cursor of the console to a target destination
	// used for directional player move
	gotoxy(x, y);
	this->cursor->setV(y, row);
	this->cursor->setH(x, column);
}

void MineSweeperGame::moveTo(CursorPosition *position) {
	// transfer the text cursor of the console to a target destination
	// used for directional player move
	gotoxy(position->x, position->y);
}

void MineSweeperGame::dispositionCursor(int8_t yDirection, int8_t xDirection) {
	// directions
	this->cursor->disposition(yDirection, xDirection);
	// prevent cursor from jumping out of table
	if(this->cursor->y > this->southY)
		this->cursor->setV(this->northY, 0);
	else if(this->cursor->y < this->northY)
		this->cursor->setV(this->southY, this->rows - 1);
		
	if(this->cursor->x > this->eastX)
		this->cursor->setH(this->westX, 0);
	else if(this->cursor->x < this->westX)
		this->cursor->setH(this->eastX, this->columns - 1);
		
	this->moveTo(this->cursor);
}

void MineSweeperGame::draw() {
	// set console background to white(=7) and text color to brown(=4)
	system("color 74");
	// draw the empty table
	// the table is designed by a specific order of | and -- prints
	for(int i = 0; i < VERTICAL_SCALE; i++)
		cout << endl;
		
	string leftMargin = "";
	// create a tab string for creating a space between left side of the table and the left side of console
	for(uint8_t i = 0; i < HORIZONTAL_STEP - 3; i++, leftMargin += "\t"); 
	
	for(uint8_t i = 0; i <= this->rows;i++)
	{
		cout << leftMargin;
		for(uint8_t j = 0;j < this->columns;j++)
			cout << " ---";

		cout << endl << leftMargin;
		
		if(i < this->rows) {
			for(uint8_t j = 0;j <= this->columns;j++)
				cout << "|   ";
				
			cout << endl;
		}

	}
	
	// move to first cell
	this->cursor->update(this->northY, this->westX, this->northY, this->westX);
	this->moveTo(this->cursor);
}


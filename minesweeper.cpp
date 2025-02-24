#include "minesweeper.h"
#include <windows.h>
#include <stdlib.h>
#include <iostream>
#include "utils.h"

using namespace std;

MineSweeperGame::MineSweeperGame(uint8_t _rows, uint8_t _columns) : VERTICAL_SCALE(_rows / (2.0 + _rows / 5)), HORIZONTAL_SCALE(_columns / (2.0f + _columns / 10)),
HORIZONTAL_STEP((uint8_t)HORIZONTAL_SCALE / 2 + 1), VERTICAL_STEP((uint8_t)VERTICAL_SCALE / 2 + 1) {
	// initialize and reset the game state(including the game table)
	// cursor is set on (0, 0)
	this->rows = _rows;
	this->columns = _columns;
	this->state = new GameState(this->rows, this->columns);
	uint8_t offsetX = this->columns / 10, offsetY = this->rows / 5;
	this->westX = HORIZONTAL_SCALE * offsetX - (uint8_t)HORIZONTAL_SCALE / offsetX;
	this->eastX = this->westX + (this->columns - 1) * HORIZONTAL_STEP;
	this->northY = VERTICAL_SCALE * offsetY - (uint8_t)VERTICAL_SCALE / offsetY;
	this->southY = this->northY + (this->rows - 1) * VERTICAL_STEP;

	this->cursor = this->newCursor();
}

void MineSweeperGame::pause() const {
	std::cout << std::endl;
	system("pause");	
}

uint8_t MineSweeperGame::getWindowWidth() const {
	return this->columns * HORIZONTAL_SCALE;
}

uint8_t MineSweeperGame::getWindowHeight() const {
	return this->rows * VERTICAL_SCALE;
}

void MineSweeperGame::resizeConsole() const{
	// FIXME: Seems not working on windows 11

	// use windows.h library to resize the console into the desired width and heights
	COORD coord;
	const uint8_t width = this->getWindowWidth(), height = this->getWindowHeight();
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

string MineSweeperGame::getDimensions() const {
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

void MineSweeperGame::openBlock(const uint8_t row, const uint8_t column) {
	try {
		state->openBlock(row, column);
	}
	catch (std::invalid_argument) {
		cout << (char)7;
	}
	catch (std::logic_error) {
		// TODO: You Lose
	}
}

void MineSweeperGame::showMessage(const string message, const string messageTag)
{
	gotoxy(MESSAGE_ROW_INDEX, 1);
	this->recentMessage = message;
	cout << "\t" << messageTag << ": " << this->recentMessage;
	this->dispositionCursor(0, 0);
}

void MineSweeperGame::clearMessageBox()
{
	gotoxy(MESSAGE_ROW_INDEX, 1);
	const uint8_t width = this->getWindowWidth();
	for (int i = 0; i < width; i++) {
		cout << " ";
	}
	this->dispositionCursor(0, 0);
	this->recentMessage = "";
}

bool MineSweeperGame::isMessageBoxEmpty() const {
	return this->recentMessage.empty();
}

void MineSweeperGame::move(int8_t direction) {
	// TODO: 
}
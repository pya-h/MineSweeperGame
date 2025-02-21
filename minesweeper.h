#ifndef MINESWEEPER_H
#define MINESWEEPER_H
#include <string>
#include <stdint.h>
#include "entities.h"

#define EMPTY 0


class MineSweeperGame {
private:
	GameState *state; // conatins the currnt table, previous state of the table and the [next state of the table(if the user has performed Undo)]
	uint8_t rows, columns; // the game table will be dynamically constructed by these params
	const float VERTICAL_SCALE;
	const float HORIZONTAL_SCALE;

	const uint8_t HORIZONTAL_STEP;
	const uint8_t VERTICAL_STEP;

	void move(uint8_t direction); // TODO: move in a specific direction
	void moveTo(uint8_t y = 0, uint8_t x = 0);
	void moveTo(CursorPosition *position);
	void moveTo(uint8_t y, uint8_t x, uint8_t row, uint8_t column);

	uint8_t westX, eastX, northY, southY;
	
	CursorPosition *cursor;

public:
	MineSweeperGame(uint8_t _rows = 16, uint8_t _columns = 30): VERTICAL_SCALE(_rows / (2.0 + _rows / 5)), HORIZONTAL_SCALE(_columns / (2.0f + _columns / 10)),
			HORIZONTAL_STEP((uint8_t)HORIZONTAL_SCALE / 2 + 1), VERTICAL_STEP((uint8_t)VERTICAL_SCALE / 2 + 1) {
		// initialize and reset the game state(including the game table)
		// cursor is set on (0, 0)
		this->rows = _rows;
		this->columns = _columns;
		this->state = new GameState(this->rows, this->columns);
		uint8_t offsetX = this->columns / 10, offsetY = this->rows / 5;
		this->westX = HORIZONTAL_SCALE * offsetX - (uint8_t)HORIZONTAL_SCALE/offsetX;
		this->eastX = this->westX + (this->columns - 1) * HORIZONTAL_STEP;
		this->northY = VERTICAL_SCALE * offsetY - (uint8_t)VERTICAL_SCALE/offsetY;
		this->southY = this->northY + (this->rows - 1) * VERTICAL_STEP;

		this->cursor = this->newCursor();
	}

	~MineSweeperGame(); // class destructor; used for gameOver function for example.

	CursorPosition *newCursor(uint8_t x0 = 0, uint8_t y0 = 0) {
		return new CursorPosition(x0, y0, HORIZONTAL_STEP, VERTICAL_STEP);
	}

	void resizeConsole(); // update the dimensions of the console based on the rows and columns of the table
	
	std::string getDimensions(); // returns a string containing the dimens of the game table (16x30 by default).
	
	void draw();
	
	void pause();
	void dispositionCursor(int8_t yDirection, int8_t xDirection);
};
#endif // MINESWEEPER_H
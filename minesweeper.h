#ifndef MINESWEEPER_H
#define MINESWEEPER_H
#include <string>
#include <stdint.h>

#define EMPTY 0

struct CursorPosition {
	uint8_t y, x;
	uint8_t horizontalStep, verticalStep;

	CursorPosition(uint8_t _y = 0, uint8_t _x = 0, uint8_t horizontalStep = 1, uint8_t verticalStep = 1) {
		update(_y, _x);
		this->horizontalStep = horizontalStep;
		this->verticalStep = verticalStep;

	}
	
	void update(uint8_t _y, uint8_t _x) {
		y = _y;
		x = _x;
	}
	
	void disposition(int8_t dy, int8_t dx) {
		// this function will update the cursor position,
		// considering its current position => x += dx, y += dy
		x += dx * horizontalStep;
		y += dy * verticalStep;
	}
	
	void setX(uint8_t _x) {
		x = _x;
	}
	
	void setY(uint8_t _y) {
		y = _y;
	}
};

struct GameState {
	uint8_t **table; // the 2D table and all previous states of it
	
	GameState *next, *previous; // this creates a link list; 
	// using this link list the player can perform Undo and Redo moves;
	GameState(const uint8_t rows, const uint8_t columns) {
		// initialize table;
		next = previous = nullptr;
		table = new uint8_t*[rows];
		for(int i = 0; i < rows; i++) {
			table[i] = new uint8_t[columns];
			// reset table array
			for(int j = 0; j < columns; table[i][j] = EMPTY, j++);

		}
		
	}
};

class MineSweeperGame {
private:
	GameState *state; // conatins the currnt table, previous state of the table and the [next state of the table(if the user has performed Undo)]
	uint8_t rows, columns; // the game table will be dynamically constructed by these params
	const float VERTICAL_SCALE;
	const float HORIZONTAL_SCALE;

	const uint8_t HORIZONTAL_STEP;
	const uint8_t VERTICAL_STEP;

	void move(uint8_t direction); // move in a specific direction
	void moveTo(uint8_t y = 0, uint8_t x = 0);
	void moveTo(CursorPosition *position);
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
#ifndef MINESWEEPER_H
#define MINESWEEPER_H
#include <string>
#include <stdint.h>

#define EMPTY 0
#define VERTICAL_SCALE 3
#define HORIZONTAL_SCALE 4

const uint8_t HORIZONTAL_STEP = (uint8_t)HORIZONTAL_SCALE/2 + 1,
	VERTICAL_STEP = (uint8_t)VERTICAL_SCALE/2 + 1;

struct CursorPosition {
	uint8_t y, x;
	
	CursorPosition(uint8_t _y = 0, uint8_t _x = 0) {
		update(_y, _x);
	}
	
	void update(uint8_t _y, uint8_t _x) {
		y = _y;
		x = _x;
	}
	
	void disposition(int8_t dy, int8_t dx) {
		// this function will update the cursor position,
		// considering its current position => x += dx, y += dy
		x += dx * HORIZONTAL_STEP;
		y += dy * VERTICAL_STEP;
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
	GameState(const unsigned int rows, const unsigned int columns) {
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
	void move(uint8_t direction); // move in a specific direction
	void moveTo(uint8_t y = 0, uint8_t x = 0);
	void moveTo(CursorPosition &position);
	uint8_t westX, eastX, northY, southY;
	
	CursorPosition cursor;

public:
	MineSweeperGame(uint8_t _rows = 16, uint8_t _columns = 30) { 	
		// initialize and reset the game state(including the game table)
		// cursor is set on (0, 0)
		this->rows = _rows;
		this->columns = _columns;
		this->state = new GameState(this->rows, this->columns);
		this->westX = HORIZONTAL_SCALE * 4 + 1;
		this->eastX = this->westX + (this->columns - 1) * HORIZONTAL_STEP;
		this->northY = VERTICAL_SCALE + 2;
		this->southY = this->northY + (this->rows - 1) * VERTICAL_STEP;

	}
	~MineSweeperGame(); // class destructor; used for gameOver function for example.
	
	void resizeConsole(); // update the dimensions of the console based on the rows and columns of the table
	
	std::string getDimensions(); // returns a string containing the dimens of the game table (16x30 by default).
	
	void draw();
	
	void pause();
	void dispositionCursor(uint8_tDirection, uint8_t xDirection);
};
#endif // MINESWEEPER_H
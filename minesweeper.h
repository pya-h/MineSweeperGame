#ifndef MINESWEEPER_H
#define MINESWEEPER_H
#include <string>

#define EMPTY 0
#define VERTICAL_SCALE 3
#define HORIZONTAL_SCALE 4

const short HORIZONTAL_STEP = (short)HORIZONTAL_SCALE/2 + 1,
	VERTICAL_STEP = (short)VERTICAL_SCALE/2 + 1;

struct CursorPosition {
	short y, x;
	
	CursorPosition(short _y = 0, short _x = 0) {
		update(_y, _x);
	}
	
	void update(short _y, short _x) {
		y = _y;
		x = _x;
	}
	
	void disposition(short dy, short dx) {
		// this function will update the cursor position,
		// considering its current position => x += dx, y += dy
		x += dx * HORIZONTAL_STEP;
		y += dy * VERTICAL_STEP;
	}
	
	void setX(short _x) {
		x = _x;
	}
	
	void setY(short _y) {
		y = _y;
	}
};

struct GameState {
	short **table; // the 2D table and all previous states of it
	
	GameState *next, *previous; // this creates a link list; 
	// using this link list the player can perform Undo and Redo moves;
	GameState(const unsigned int rows, const unsigned int columns) {
		// initialize table;
		next = previous = nullptr;
		table = new short*[rows];
		for(int i = 0; i < rows; i++) {
			table[i] = new short[columns];
			// reset table array
			for(int j = 0; j < columns; table[i][j] = EMPTY, j++);

		}
		
	}
};

class MineSweeperGame {
private:
	GameState *state; // conatins the currnt table, previous state of the table and the [next state of the table(if the user has performed Undo)]
	unsigned short int rows, columns; // the game table will be dynamically constructed by these params
	void move(short direction); // move in a specific direction
	void moveTo(short y = 0, short x = 0);
	void moveTo(CursorPosition &position);
	short westX, eastX, northY, southY;
	
	CursorPosition cursor;

public:
	MineSweeperGame(unsigned short int _rows = 16, unsigned short int _columns = 30) { 	
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
	void dispositionCursor(short yDirection, short xDirection);
};
#endif // MINESWEEPER_H
#ifndef MINESWEEPER_H
#define MINESWEEPER_H
#include <windows.h>
#include <iostream>
#include <string>
#include <stdlib.h>

#define EMPTY 0
#define VERTICAL_SCALE 3
#define HORIZONTAL_SCALE 4

struct GameState {
	short **table; // the 2D table and all previous states of it
	
	GameState *next, *previous; // this creates a link list; 
	// using this link list the player can perform Undo and Redo moves;
	GameState(const unsigned int rows, const unsigned int columns) {
		// initialize table;
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
	GameState *state;
	unsigned short int rows, columns;
	void moveTo(short int x, short y);
	
public:
	MineSweeperGame(unsigned short int _rows, unsigned short int _columns) : rows(_rows), columns(_columns) { 	
		this->state = new GameState(this->rows, this->columns);
	}
	~MineSweeperGame();
	void resizeConsole(); // update the dimensions of the console based on the rows and columns of the table
	
	std::string getDimensions();
	
	void draw();
	
	void pause() {
		std::cout << std::endl;
		system("pause");
	}
};
#endif // MINESWEEPER_H
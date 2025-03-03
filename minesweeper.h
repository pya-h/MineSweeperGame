#ifndef MINESWEEPER_H
#define MINESWEEPER_H
#include <string>
#include <stdint.h>
#include "entities.h"

class MineSweeperGame {
private:
	const uint8_t GAME_BAR_ROW_INDEX = 1;
	std::string recentMessage = "";

	const float VERTICAL_SCALE;
	const float HORIZONTAL_SCALE;
	const uint8_t HORIZONTAL_STEP;
	const uint8_t VERTICAL_STEP;

	GameState* state; // conatins the currnt table, previous state of the table and the [next state of the table(if the user has performed Undo)]
	uint8_t rows, columns; // the game table will be dynamically constructed by these params
	uint8_t westX, eastX, northY, southY;
	Player* player;
	CursorPosition *cursor;

public:
	MineSweeperGame(Player& player, uint8_t _rows = 16, uint8_t _columns = 30);

	~MineSweeperGame(); // class destructor; used for gameOver function for example.

	void moveTo(uint8_t y = 0, uint8_t x = 0);
	void moveTo(CursorPosition* position);
	void moveTo(uint8_t y, uint8_t x, uint8_t row, uint8_t column);

	uint8_t getWindowWidth() const;
	uint8_t getWindowHeight() const;

	CursorPosition *newCursor(uint8_t x0 = 0, uint8_t y0 = 0) {
		return new CursorPosition(x0, y0, HORIZONTAL_STEP, VERTICAL_STEP);
	}

	void resizeConsole() const; // update the dimensions of the console based on the rows and columns of the table
	
	std::string getDimensions() const; // returns a string containing the dimens of the game table (16x30 by default).
	
	void draw();
	
	void pause() const;
	void dispositionCursor(int8_t yDirection, int8_t xDirection);
	uint8_t countDigits(uint64_t x) const;
	void openCurrentBlock();
	void clearMessageBox();
	bool isMessageBoxEmpty() const;
	void showMessage(const std::string message, const std::string messageTag = "ERROR");
	void showBlockValue(const MineBlock* block);
	void showPlayerPoint();
	void defaultColoring();
};
#endif // MINESWEEPER_H
#pragma once
#ifndef ENTITIES_H
#define ENTITIES_H

#include <stdint.h>
#include <vector>
#include <random>
#include <iostream>
#include <ctime>

struct CursorPosition {
	uint8_t y, x;
	int8_t row, column;
	uint8_t horizontalStep, verticalStep;

	CursorPosition(uint8_t _y = 0, uint8_t _x = 0, uint8_t horizontalStep = 1, uint8_t verticalStep = 1) {
		this->horizontalStep = horizontalStep;
		this->verticalStep = verticalStep;
		update(_y, _x);
	}

	CursorPosition(CursorPosition& other) {
		this->assign(&other);
	}

	void update(uint8_t _y, uint8_t _x, uint8_t yOffset = 0, uint8_t xOffset = 0) {
		this->setX(_x, xOffset);
		this->setY(_y, yOffset);
	}

	void disposition(int8_t dy, int8_t dx) {
		// this function will update the cursor position,
		// considering its current position => x += dx, y += dy
		x += dx * horizontalStep;
		y += dy * verticalStep;
		column += dx;
		row += dy;
	}

	void setX(uint8_t _x, bool syncColumn = true) {
		x = _x;
		if (syncColumn) {
			column = x / this->horizontalStep;
		}
	}

	void setY(uint8_t _y, bool syncRow = true) {
		y = _y;
		if (syncRow) {
			row = y / this->verticalStep;
		}
	}

	void setX(uint8_t _x, uint8_t offset) {
		x = _x;
		column = (x - offset) / this->horizontalStep;
	}

	void setY(uint8_t _y, uint8_t offset) {
		y = _y;
		row = (y - offset) / this->verticalStep;
	}

	void setRow(int8_t _row) {
		this->row = _row;
	}

	void setColumn(int8_t _col) {
		this->column = _col;
	}

	void setH(uint8_t _x, int8_t _column) {
		this->x = _x;
		this->column = _column;
	}

	void setV(uint8_t _y, int8_t _row) {
		this->y = _y;
		this->row = _row;
	}

	void teleport(CursorPosition* destination) {
		this->x = destination->x;
		this->y = destination->y;
		this->row = destination->row;
		this->column = destination->column;
	}

	void teleport(CursorPosition &destination) {
		this->teleport(&destination);
	}

	void assign(CursorPosition* target) {
		this->teleport(target);
		this->horizontalStep = target->horizontalStep;
		this->verticalStep = target->verticalStep;
	}

	void assign(CursorPosition& target) {
		this->assign(&target);
	}

};

struct MineBlock {
	uint8_t value;
	uint8_t row, column;
	bool isMined;
	bool isBombed;
	bool isIdentified;

	MineBlock(uint8_t _row, uint8_t _column, uint8_t _value = 1, bool _isBombed = false) {
		this->row = _row;
		this->column = _column;
		this->value = _value;
		this->isBombed = _isBombed;
		this->isMined = this->isIdentified = false;
	}

	void mine(uint8_t bombChance = 20, uint8_t maxBlockValue = 10, bool onlyIfSafe = false) {
		this->identify(bombChance, maxBlockValue);

		if (this->isMined) {
			throw std::invalid_argument("Block has already been mined!");
		}
		if (onlyIfSafe && this->isBombed)
			return;
		this->isMined = true;
	}

	void identify(uint8_t bombChance = 10, uint8_t maxBlockValue = 10) {
		if (isIdentified) {
			return;
		}
		std::random_device randomDevice;
		std::mt19937 generator(randomDevice());
		std::uniform_int_distribution<short> disturbation(0, 100);
		uint8_t chance = disturbation(generator);

		this->isIdentified = true;
		if (chance < bombChance) {
			this->isBombed = true;
			this->value = 0;
			return;
		}
		this->value = chance % maxBlockValue + 1;
	}
};

struct GameState {
	std::vector<std::vector<MineBlock>> table; // the 2D table and all previous states of it
	const uint8_t USER_BOMB_CHANCE = 20, MAX_BLOCK_VALUE = 10;
	// using this link list the player can perform Undo and Redo moves;
	GameState(const uint8_t rows, const uint8_t columns) {
		// initialize table;

		std::vector<MineBlock> row;
		for (int i = 0; i < rows; i++) {
			
			// reset table array
			for (int j = 0; j < columns; j++) {
				row.push_back(MineBlock(i, j));
			}																																																																																																																																																																																																																																																																																																																																																																																																																						_abs64;
			table.push_back(row);
		}

	};

	~GameState() {
		this->table.clear();
	}

	MineBlock *openBlock(uint8_t row, uint8_t column) {
		const auto& block = this->getBlock(row, column);
		block->mine(USER_BOMB_CHANCE, MAX_BLOCK_VALUE);
		return block;
	}

	void openBlockIfSafe(MineBlock *block) {
		block->mine(USER_BOMB_CHANCE, MAX_BLOCK_VALUE, true);
	}

	MineBlock* getBlock(const uint8_t row, const uint8_t column) {
		if (row >= this->table.size() || column >= this->table[row].size()) {
			throw std::invalid_argument("No such block!");
		}
		return &(this->table[row][column]);
	}
};

struct Player {
	std::time_t id, startedAt;
	uint16_t points;

	Player() {
		this->startedAt = 0;
		this->points = 0;
		this->id = std::time(nullptr);
	}

	void start() {
		this->startedAt = std::time(nullptr);
	}

	time_t getElapsedTime() const {
		return std::time(nullptr) - this->startedAt;
	}

	void consumeBlock(const MineBlock* block) {
		if (!block->isMined) {
			throw std::invalid_argument("Block not mined!");
		}
		this->points += block->value;
	}
};
#endif
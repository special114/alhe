#pragma once

#include <iostream>

class Board
{
private:
	unsigned size;
	unsigned** fields;
public:
	Board() {}
	Board(unsigned size);
	~Board();
	unsigned getSize();

	friend std::ostream& operator<<(std::ostream& os, const Board& board);
};

std::ostream& operator<<(std::ostream& os, const Board& board);
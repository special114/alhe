#pragma once
#include <iostream>
#include <vector>

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
	unsigned& getField(unsigned column, unsigned row);
	unsigned* getRow(unsigned row);

	friend std::ostream& operator<<(std::ostream& os, const Board& board);
};

std::ostream& operator<<(std::ostream& os, const Board& board);
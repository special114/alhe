#include "Board.h"

using namespace std;

Board::Board(unsigned size) {
	this->size = size;
	this->fields = new unsigned*[size];
	for (int i = 0; i < size; ++i) {
		this->fields[i] = new unsigned[size]();
	}
}

void Board::copyValues(Board& _board) {
	this->size = _board.getSize();
	this->fields = new unsigned* [size];
	for (unsigned i = 0; i < size; ++i) {
		this->fields[i] = new unsigned[size]();
	}

	for (unsigned i = 0; i < size; ++i) {
		for (unsigned j = 0; j < size; ++j) {
			this->fields[i][j] = _board.getField(i, j);
		}
	}
}

Board::~Board() {
	for (int i = 0; i < size; ++i) {
		delete[] fields[i];
	}
	delete[] fields;
}

unsigned Board::getSize()
{
	return size;
}

unsigned& Board::getField(unsigned column, unsigned row)
{
	return fields[row][column];
}

unsigned* Board::getRow(unsigned row)
{
	return fields[row];
}

ostream& operator<<(ostream& os, const Board& board) {
	for (int i = 0; i < board.size; ++i) {
		for (int j = 0; j < board.size; ++j) {
			os << board.fields[i][j] << " ";
		}
		os << endl;
	}
	return os;
}

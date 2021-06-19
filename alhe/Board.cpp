#include "Board.h"

using namespace std;

Board::Board(unsigned size) {
	this->size = size;
	this->fields = new unsigned*[size];
	for (int i = 0; i < size; ++i) {
		this->fields[i] = new unsigned[size]();
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

ostream& operator<<(ostream& os, const Board& board) {
	for (int i = 0; i < board.size; ++i) {
		for (int j = 0; j < board.size; ++j) {
			os << board.fields[i][j] << " ";
		}
		os << endl;
	}
	return os;
}

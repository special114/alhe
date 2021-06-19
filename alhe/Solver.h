#pragma once

#include <string>
#include <vector>

#include "Board.h"

class Solver
{
protected:
	Board& board;
	unsigned* top_constraints;
	unsigned* bot_constraints;
	unsigned* left_constraints;
	unsigned* right_constraints;

	unsigned factorial(unsigned n);
	unsigned getSize();
public:
	Solver(Board& _board);
	void init();
	void randomInitialization();
	//bool isValidPosition(unsigned height, unsigned x, unsigned y);
	//std::vector<std::string> split(const std::string& s, char deliliter);
};


#pragma once

#include <string>
#include <vector>

#include "Board.h"

class Solver
{
private:
	Board board;
	unsigned* top_constraints;
	unsigned* bot_constraints;
	unsigned* left_constraints;
	unsigned* right_constraints;
public:
	Solver(Board& b);
	void init();
	std::vector<std::string> split(const std::string& s, char deliliter);
};


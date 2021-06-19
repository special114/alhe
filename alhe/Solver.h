#pragma once

#include <string>
#include <vector>
#include <sstream>

#include "Board.h"

class Solver
{
protected:
	Board& board;
	std::vector<unsigned> top_constraints;
	std::vector<unsigned> bot_constraints;
	std::vector<unsigned> left_constraints;
	std::vector<unsigned> right_constraints;

	unsigned getSize();
public:
	Solver(Board& _board);
	void init();
	//bool isValidPosition(unsigned height, unsigned x, unsigned y);
	void initConstraints(std::vector<unsigned>& constraints);
	std::vector<unsigned> split(const std::string& s, char deliliter);
};


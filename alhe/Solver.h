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
	void init();
	void initConstraints(std::vector<unsigned>& constraints);
public:
	Solver(Board& _board);
	//bool isValidPosition(unsigned height, unsigned x, unsigned y);
	std::vector<unsigned> split(const std::string& s, char deliliter);
};


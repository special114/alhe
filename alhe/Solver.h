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

	unsigned factorial(unsigned n);
	unsigned getSize();
	void init();
	void initConstraints(std::vector<unsigned>& constraints);
public:
	Solver(Board& _board);
	void randomInitialization(Board& _board);

	std::vector<unsigned> split(const std::string& s, char deliliter);
};


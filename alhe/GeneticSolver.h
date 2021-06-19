#pragma once
#include "Solver.h"

class GeneticSolver : public Solver
{
private:
	unsigned population_size;

	Board& genetareBoard();
public:
	GeneticSolver(unsigned _population_size);
	void solve();
};


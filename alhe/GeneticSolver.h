#pragma once
#include <limits>

#include "Solver.h"

class GeneticSolver : public Solver
{
private:
	unsigned population_size;
	Board** population;

	Board* genetareBoard();
public:
	GeneticSolver(Board& _board, unsigned _population_size);
	~GeneticSolver();
	void solve();
	int assessPopulation();
	void performCrossover(Board* b1, Board* b2);
	void print();
};


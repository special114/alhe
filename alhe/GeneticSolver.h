#pragma once
#include <limits>
#include <functional>
#include <algorithm>
#include <random>

#include "Solver.h"

struct Individual {
	Board* board = nullptr;
	double score;
};
struct Range {
	double start;
	double end;
};

class GeneticSolver : public Solver
{
private:
	unsigned population_size;
	Individual* population;
	Individual* children;
	double* population_scores;
	Range* probability;
	bool solutionFound = false;

	Board* genetareBoard();
public:
	GeneticSolver(Board& _board, unsigned _population_size);
	~GeneticSolver();
	bool solve();
	void assessPopulation();
	void assess(Individual& in);
	void performSelection();
	unsigned getMaxScore();
	void performCrossover();
	void permormMutation();
	void performSuccession();
	Individual createChild(Individual& in1, Individual& in2);
	static bool comp(Individual& in1, Individual& in2);
	void print();
};


#pragma once
#include <limits>
#include <functional>
#include <algorithm>
#include <random>

#include "Solver.h"

const int MUTATION = 0.5;

class Individual {
public:
	Board* board;
	double score;

	Individual(int size) {
		board = new Board(size);
	}

	~Individual() {
		delete board;
	}
};
struct Range {
	double start;
	double end;
};

class GeneticSolver : public Solver
{
private:
	unsigned population_size;
	Individual** population;
	Individual** children;
	double* population_scores;
	Range* probability;
	bool solutionFound = false;

	Board* genetareBoard();
public:
	GeneticSolver(Board& _board, unsigned _population_size, std::vector<std::vector<unsigned>> constraints);
	~GeneticSolver();
	bool solve();
	void assessPopulation(Individual** population, bool isChildren);
	void assess(Individual* in);
	void performSelection();
	unsigned getMaxScore();
	void performCrossover();
	void performMutation();
	void performSuccession();
	Individual* createChild(Individual* in1, Individual* in2);
	static bool comp(Individual* in1, Individual* in2);
	void print();
};


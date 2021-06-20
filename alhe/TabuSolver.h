#pragma once
#include "Solver.h"
#include <map>
#include <list>

struct Row {
	Row(unsigned _lossFunction) : lossFunction(_lossFunction) {}

	unsigned lossFunction;
	std::vector<std::pair<unsigned, unsigned>> fieldsToSwap;
	std::vector<std::vector<unsigned>> tabuList;
};

class TabuSolver : public Solver
{
public:
	TabuSolver(Board& _board, std::vector<std::vector<unsigned>> constraints);
	void execute();

private:
	unsigned fieldLossFunction(unsigned column, unsigned row);
	unsigned calculateRowLossFunction(unsigned row);
	void calculateRowsLossFunction();
	int lossFunctionDiffAfterSwap(unsigned column, unsigned row, unsigned neighbour);

	void addToTabu(unsigned row);
	bool checkIfInTabu(unsigned row);

	void iterateThroughNeighboursInRow(unsigned row);
	void makeBestSwap(unsigned row);

	std::vector<Row> rowParams;
	const int TABU_LENGTH = 4;
	const int LOOP_RESET = 50000;
};


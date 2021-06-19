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
	TabuSolver(Board& _board);
	void execute();

private:
	unsigned fieldLossFunction(unsigned column, unsigned row);
	unsigned calculateRowLossFunction(unsigned row);
	void calculateRowsLossFunction();
	int lossFunctionDiffAfterSwap(unsigned column, unsigned row, unsigned neighbour);
	int checkValueUniqueness(unsigned column, unsigned value);

	void addToTabu(unsigned row);
	bool checkIfInTabu(unsigned row);

	void iterateThroughNeighboursInRow(unsigned row);
	void makeBestSwap(unsigned row);

	std::vector<Row> rowParams;
	const int LOWEST_VALUE = -2147483648;
	const int TABU_LENGTH = 4;
	const int LOOP_RESET = 10000;
	//std::vector<unsigned> 
};


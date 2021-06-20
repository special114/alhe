#include "TabuSolver.h"
#include "random"

using namespace std;

TabuSolver::TabuSolver(Board& _board, vector<vector<unsigned>> constraints) : Solver(_board, constraints) {

	for (unsigned i = 0; i < getSize(); ++i) {
		rowParams.push_back(Row(0));
	}
}

void TabuSolver::execute()
{
	int loops = 0;
	randomInitialization(board);
	cout << board << "\n";

	while ( !isSolution(board) ) {
		if (loops == LOOP_RESET) {
			cout << "Reset!\n";
			randomInitialization(board);
			cout << board << "\n";
			loops = 0;
		}

		calculateRowsLossFunction();

		for (unsigned row = 0; row < getSize(); ++row) {
			iterateThroughNeighboursInRow(row);
			makeBestSwap(row);
			addToTabu(row);
		}

		++loops;
	}
	cout << loops<<'\n';
}

void TabuSolver::calculateRowsLossFunction()
{
	for (unsigned row = 0; row < getSize(); ++row) {
		rowParams[row].lossFunction = calculateRowLossFunction(row);
	}
}

void TabuSolver::iterateThroughNeighboursInRow(unsigned row)
{
	const int LOWEST_VALUE = -2147483648;
	int maxDiff = -LOWEST_VALUE;
	rowParams[row].fieldsToSwap.clear();
	for (unsigned column = 0; column < getSize(); ++column) {
		for (unsigned neighbour = 0; neighbour < getSize(); ++neighbour) {
			if (neighbour == column) {
				continue;
			}

			int diff = lossFunctionDiffAfterSwap(column, row, neighbour);
			if (diff > maxDiff) {
				maxDiff = diff;
				rowParams[row].fieldsToSwap.clear();
				rowParams[row].fieldsToSwap.push_back(std::make_pair(column, neighbour));
			}
			if (diff == maxDiff) {
				rowParams[row].fieldsToSwap.push_back(std::make_pair(column, neighbour));
			}
		}
	}

	rowParams[row].lossFunction -= maxDiff;
}

unsigned TabuSolver::calculateRowLossFunction(unsigned row)
{
	unsigned lossValue = 0;
	for (unsigned column = 0; column < getSize(); ++column) {
		lossValue += fieldLossFunction(column, row);
	}

	return lossValue;
}

unsigned TabuSolver::fieldLossFunction(unsigned column, unsigned row)
{
	unsigned lossFunction = 0;

	lossFunction += checkRowConstraint(board, row) * getSize();
	lossFunction += checkColumnConstraint(board, column) * getSize();
	lossFunction += checkValueUniqueness(board, column, board.getField(column, row));

	return lossFunction;
}

int TabuSolver::lossFunctionDiffAfterSwap(unsigned column, unsigned row, unsigned neighbour)
{
	const int LOWEST_VALUE = -2147483648;
	unsigned currLossValue = rowParams[row].lossFunction;
	std::swap(board.getField(column, row), board.getField(neighbour, row));
	if (checkIfInTabu(row)) {
		return LOWEST_VALUE;
	}

	unsigned lossValueAfterSwap = calculateRowLossFunction(row);
	std::swap(board.getField(column, row), board.getField(neighbour, row));
	int diff = currLossValue - lossValueAfterSwap;

	return diff;
}

void TabuSolver::addToTabu(unsigned row)
{

	vector<unsigned> tabuRow;
	for (unsigned column = 0; column < getSize(); ++column) {
		tabuRow.push_back(board.getField(column, row));
	}

	auto& tabuList = rowParams[row].tabuList;
	tabuList.push_back(tabuRow);

	if (tabuList.size() > TABU_LENGTH)
		tabuList.erase( tabuList.begin() );
}

bool TabuSolver::checkIfInTabu(unsigned row)
{
	vector<unsigned> tabuRow;
	for (unsigned column = 0; column < getSize(); ++column) {
		tabuRow.push_back(board.getField(column, row));
	}

	for (auto tabu : rowParams[row].tabuList) {
		if (tabu == tabuRow) {
			return true;
		}
	}

	return false;
}

void TabuSolver::makeBestSwap(unsigned row)
{
	if (rowParams[row].fieldsToSwap.size() == 0)
		return;

	/*int lastElemIdx = (int)rowParams[row].fieldsToSwap.size() - 1;
	std::random_device rd;
	std::mt19937 gen(rd());
	std::uniform_int_distribution<> distrib(0, lastElemIdx);*/
	int randomSwap = std::rand() % rowParams[row].fieldsToSwap.size();

	auto fieldsToSwap = rowParams[row].fieldsToSwap[randomSwap];

	std::swap(board.getField(fieldsToSwap.first, row), board.getField(fieldsToSwap.second, row));

}
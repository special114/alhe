#include "Solver.h"
#include <random>

using namespace std;

unsigned Solver::getSize()
{
	return board.getSize();
}

Solver::Solver(Board& _board) : board(_board) {
	//init();
}


void Solver::init() {
	initConstraints(top_constraints);
	initConstraints(bot_constraints);
	initConstraints(left_constraints);
	initConstraints(right_constraints);
}

void Solver::initConstraints(vector<unsigned>& constraints) {
	string line;
	getline(cin, line);
	constraints = split(line, ' ');
}

void Solver::randomInitialization(Board& _board)
{
    unsigned* numbers = new unsigned[getSize()];

    for (unsigned row = 0; row < getSize(); ++row) {
        for (unsigned i = 0; i < getSize(); ++i) {
            numbers[i] = i + 1;
        }

        std::random_device rd;
        std::mt19937 gen(rd());
        std::uniform_int_distribution<> distrib(0, factorial(getSize()));
        unsigned permutation = distrib(gen);
        for (unsigned i = 0; i < permutation; ++i) {
            std::next_permutation(numbers, numbers + getSize());
        }

        for (unsigned column = 0; column < getSize(); ++column) {
            _board.getField(column, row) = numbers[column];
        }
    }

    delete[] numbers;
}

bool Solver::isSolution(Board& board)
{
    for (int column = 0; column < getSize(); ++column) {
        if (!isColumnUnique(board, column) || !isColumnConstraintApproved(board, column)) {
            return false;
        }

        for (int row = 0; row < getSize(); ++row) {
            if (!isRowUnique(board, row) || !isRowConstraintApproved(board, column)) {
                return false;
            }
        }
    }

    return true;
}

bool Solver::isColumnUnique(Board& board, unsigned column)
{
    bool* numbers = new bool[getSize()];
    for (unsigned i = 0; i < getSize(); ++i) {
        numbers[i] = false;
    }

    for (unsigned row = 0; row < getSize(); ++row) {
        if (numbers[board.getField(column, row) - 1] == true)
            return false;
        numbers[board.getField(column, row) - 1] = true;
    }



    delete[] numbers;
    return true;
}

bool Solver::isColumnConstraintApproved(Board& board, unsigned column)
{
    unsigned seenPyramids = 0;
    unsigned highestPyramid = 0;

    if (top_constraints[column] != 0) {
        for (unsigned row = 0; row < getSize(); ++row) {
            unsigned currentPyramid = board.getField(column, row);

            if (currentPyramid > highestPyramid) {
                highestPyramid = currentPyramid;
                ++seenPyramids;
            }
        }

        if (seenPyramids != top_constraints[column]) {
            return false;
        }
    }

    if (bot_constraints[column] != 0) {
        seenPyramids = 0;
        highestPyramid = 0;
        for (unsigned row = getSize() - 1; row >= 0; --row) {
            unsigned currentPyramid = board.getField(column, row);

            if (currentPyramid > highestPyramid) {
                highestPyramid = currentPyramid;
                ++seenPyramids;
            }
        }

        if (seenPyramids != bot_constraints[column]) {
            return false;
        }
    }

    return true;
}

bool Solver::isRowUnique(Board& board, unsigned row)
{
    bool* numbers = new bool[getSize()];
    for (unsigned i = 0; i < getSize(); ++i) {
        numbers[i] = false;
    }

    for (unsigned column = 0; column < getSize(); ++column) {
        if (numbers[board.getField(column, row) - 1] == true)
            return false;
        numbers[board.getField(column, row) - 1] = true;
    }

    delete[] numbers;
    return true;
}

bool Solver::isRowConstraintApproved(Board& board, unsigned row)
{
    unsigned seenPyramids = 0;
    unsigned highestPyramid = 0;

    if (left_constraints[row] != 0) {
        for (unsigned column = 0; column < getSize(); ++column) {
            unsigned currentPyramid = board.getField(column, row);

            if (currentPyramid > highestPyramid) {
                highestPyramid = currentPyramid;
                ++seenPyramids;
            }
        }

        if (seenPyramids != left_constraints[row]) {
            return false;
        }
    }

    if (right_constraints[row] != 0) {
        seenPyramids = 0;
        highestPyramid = 0;
        for (unsigned column = getSize() - 1; column >= 0; --column) {
            unsigned currentPyramid = board.getField(column, row);

            if (currentPyramid > highestPyramid) {
                highestPyramid = currentPyramid;
                ++seenPyramids;
            }
        }

        if (seenPyramids != right_constraints[row]) {
            return false;
        }
    }

    return true;
}

unsigned Solver::factorial(unsigned n)
{
    if (n > 1)
        return n * factorial(n - 1);
    else
        return 1;
}

vector<unsigned> Solver::split(const string& s, char delimiter) {
    vector<unsigned> tokens;
    string token;
    istringstream tokenStream(s);
    while (std::getline(tokenStream, token, delimiter)) {
        tokens.push_back(stoi(token));
    }
    return tokens;
}

//vector<string> split(const string& s, char delimiter) {
//	vector<string> tokens;
//	string token;
//	//istringstream tokenStream(s);
//}

//bool Solver::isValidPosition(unsigned height, unsigned x, unsigned y) {
//	if( top_constraints[x] )
//	return true;
//}
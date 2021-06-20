#include "Solver.h"
#include <random>

using namespace std;

unsigned Solver::getSize()
{
	return board.getSize();
}


Solver::Solver(Board& _board, std::vector<std::vector<unsigned>> constraints) : board(_board) {
	//init();
    top_constraints = constraints[0];
    bot_constraints = constraints[1];
    left_constraints = constraints[2];
    right_constraints = constraints[3];
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
            numbers[i] = 0;
        }

        bool numberIsAlreadyInTable;
        unsigned randomNum;
        for (int i = 0; i < getSize(); ++i) {
            numberIsAlreadyInTable = false;
            randomNum = std::rand() % getSize() + 1;
            for (unsigned j = 0; j < getSize(); ++j) {
                if (numbers[j] == randomNum) {
                    numberIsAlreadyInTable = true;
                }
            }

            if (!numberIsAlreadyInTable) {
                numbers[i] = randomNum;
            }
            else {
                --i;
            }
        }

        for (unsigned column = 0; column < getSize(); ++column) {
            _board.getField(column, row) = numbers[column];
        }
    }

    delete[] numbers;
}

bool Solver::isSolution(Board& board)
{
    for (unsigned column = 0; column < getSize(); ++column) {
        if (!isColumnUnique(board, column) || checkColumnConstraint(board, column)) {
            return false;
        }

        for (unsigned row = 0; row < getSize(); ++row) {
            if (!isRowUnique(board, row) || checkRowConstraint(board, column)) {
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

int Solver::checkColumnConstraint(Board& board, unsigned column)
{
    unsigned seenPyramids = 0;
    unsigned highestPyramid = 0;
    unsigned brokenConstraints = 0;

    if (top_constraints[column] != 0) {
        for (unsigned row = 0; row < getSize(); ++row) {
            unsigned currentPyramid = board.getField(column, row);

            if (currentPyramid > highestPyramid) {
                highestPyramid = currentPyramid;
                ++seenPyramids;
            }
        }

        if (seenPyramids != top_constraints[column]) {
            ++brokenConstraints;
        }
    }

    if (bot_constraints[column] != 0) {
        seenPyramids = 0;
        highestPyramid = 0;
        for (unsigned row = getSize() - 1; row > 0; --row) {
            unsigned currentPyramid = board.getField(column, row);

            if (currentPyramid > highestPyramid) {
                highestPyramid = currentPyramid;
                ++seenPyramids;
            }
        }

        if (seenPyramids != bot_constraints[column]) {
            ++brokenConstraints;
        }
    }

    return brokenConstraints;;
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

int Solver::checkRowConstraint(Board& board, unsigned row)
{
    unsigned seenPyramids = 0;
    unsigned highestPyramid = 0;
    unsigned brokenConstraints = 0;

    if (left_constraints[row] != 0) {
        for (unsigned column = 0; column < getSize(); ++column) {
            unsigned currentPyramid = board.getField(column, row);

            if (currentPyramid > highestPyramid) {
                highestPyramid = currentPyramid;
                ++seenPyramids;
            }
        }

        if (seenPyramids != left_constraints[row]) {
            ++brokenConstraints;
        }
    }

    if (right_constraints[row] != 0) {
        seenPyramids = 0;
        highestPyramid = 0;
        for (unsigned column = getSize() - 1; column > 0; --column) {
            unsigned currentPyramid = board.getField(column, row);

            if (currentPyramid > highestPyramid) {
                highestPyramid = currentPyramid;
                ++seenPyramids;
            }
        }

        if (seenPyramids != right_constraints[row]) {
            ++brokenConstraints;
        }
    }

    return brokenConstraints;
}

void Solver::copyValues(unsigned* toTable, unsigned* fromTable)
{
    for (unsigned i = 0; i < getSize(); ++i) {
        toTable[i] = fromTable[i];
    }
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
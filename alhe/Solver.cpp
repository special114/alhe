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
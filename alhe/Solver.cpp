#include "Solver.h"
#include <random>

using namespace std;

unsigned Solver::getSize()
{
	return board.getSize();
}

Solver::Solver(Board& _board) : board(_board) {}

void Solver::init() {
	string line;
	getline(cin, line);
	//line.s
}

void Solver::randomInitialization()
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
            board.getField(column, row) = numbers[column];
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

//vector<string> split(const string& s, char delimiter) {
//	vector<string> tokens;
//	string token;
//	//istringstream tokenStream(s);
//}

//bool Solver::isValidPosition(unsigned height, unsigned x, unsigned y) {
//	if( top_constraints[x] )
//	return true;
//}
#include "GeneticSolver.h"

using namespace std;

GeneticSolver::GeneticSolver(Board& _board, unsigned _population_size) : Solver(_board) {
	this->population_size = _population_size;
	this->population = new Board*[_population_size];

	for (int i = 0; i < population_size; ++i) {
		population[i] = genetareBoard();
	}
}

GeneticSolver::~GeneticSolver() {
	for (int i = 0; i < population_size; ++i) {
		delete population[i];
	}
	delete[] population;
}

Board* GeneticSolver::genetareBoard() {
	Board* b = new Board(board.getSize());
	randomInitialization(*b);
	return b;
}

void GeneticSolver::solve() {
	assessPopulation();
}

int GeneticSolver::assessPopulation() {
	int sum = 0;
	return 0;
}

void GeneticSolver::performCrossover(Board* b1, Board* b2) {

}

void GeneticSolver::print() {
	for (int i = 0; i < population_size; ++i) {
		cout << i << endl << *(population[i]) << endl << endl;
	}
}

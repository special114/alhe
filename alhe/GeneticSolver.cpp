
#include "GeneticSolver.h"

using namespace std;

GeneticSolver::GeneticSolver(Board& _board, unsigned _population_size) : Solver(_board) {
	this->population_size = _population_size;
	this->population = new Individual* [_population_size];
	for (int i = 0; i < _population_size; ++i) {
		population[i] = new Individual(_board.getSize());
		randomInitialization(*(population[i]->board));
	}
	this->children = new Individual* [_population_size];
	this->population_scores = new double[_population_size];
	this->probability = new Range[_population_size];
}

GeneticSolver::~GeneticSolver() {
	for (int i = 0; i < population_size; ++i) {
		delete population[i];
	}
	delete[] population;
	delete[] population_scores;
}


Board* GeneticSolver::genetareBoard() {
	Board* b = new Board(board.getSize());
	randomInitialization(*b);
	return b;
}

bool GeneticSolver::solve() {
	int i = 0;
	while (!solutionFound) {
		cout << i << endl;
		assessPopulation(population, false);
		performSelection();
		print();
		performCrossover();
		performMutation();
		assessPopulation(children, true);
		performSuccession();	
		++i;
	}
	return true;
}

void GeneticSolver::assessPopulation(Individual** population, bool isChildren) {
	for (int i = 0; i < population_size; ++i) {
		if (solutionFound) {
			return;
		}
		assess(population[i]);
	}
	sort(population, population + population_size, GeneticSolver::comp);
	
	if (!isChildren) {
		for (int i = 0; i < population_size; ++i) {
			population_scores[i] = population[i]->score;
		}

		double qmin = population_scores[0];
		double qmax = population_scores[population_size - 1];
		if (qmax != qmin) {
			for (unsigned i = 0; i < population_size; ++i) {
				population_scores[i] = 1 - ((population_scores[i] - qmin) / (qmax - qmin));
			}
		}
	}
}

void GeneticSolver::assess(Individual* individual) {
	unsigned size = individual->board->getSize();
	unsigned score = 0;

	for (unsigned i = 0; i < size; ++i) {
		if (!isRowUnique(*(individual->board), i)) {
			++score;
		}
		if (!isColumnUnique(*(individual->board), i)) {
			++score;
		}
		if (!isRowConstraintApproved(*(individual->board), i)) {
			score += size / 2;
		}
		if (!isColumnConstraintApproved(*(individual->board), i)) {
			score += size / 2;
		}
	}
	if (score == 0) {
		board.copyValues(*(individual->board));
		solutionFound = true;
		return;
	}
	individual->score = (double) score;
}

void GeneticSolver::performSelection() {
	double score_sum = 0;

	for (unsigned i = 0; i < population_size; ++i) {
		score_sum += population_scores[i];
	}

	probability[0].start = 0;
	for (unsigned i = 0; i < population_size - 1; ++i) {
		probability[i].end = probability[i].start + population_scores[i] / score_sum;
		probability[i + 1].start = probability[i].end;
	}
	probability[population_size - 1].end = 1;
}

unsigned GeneticSolver::getMaxScore() {
	double max_score = 0;
	for (unsigned i = 0; i < population_size; ++i) {
		if (population_scores[i] > max_score) {
			max_score = population_scores[i];
		}
	}
	
	return max_score;
}

void GeneticSolver::performCrossover() {
	Individual* parent1 = nullptr;
	Individual* parent2 = nullptr;

	for (unsigned i = 0; i < population_size; ++i) {
		double rand1 = rand() / RAND_MAX;
		double rand2 = rand() / RAND_MAX;

		for (unsigned j = 0; j < population_size; ++j) {
			if (rand1 >= probability[j].start && rand1 < probability[j].end) {
				parent1 = population[j];
				break;
			}
		}

		for (unsigned j = 0; j < population_size; ++j) {
			if (rand2 >= probability[j].start && rand2 < probability[j].end) {
				parent2 = population[j];
				break;
			}
		}

		children[i] = createChild(parent1, parent2);
	}
}

void GeneticSolver::performMutation() {
	unsigned board_size = board.getSize();
	for (unsigned i = 0; i < population_size; ++i) {
		for (unsigned j = 0; j < board_size; ++j) {
			for (unsigned k = 0; k < board_size; ++k) {
				if (((double)rand() / RAND_MAX) > MUTATION) {
					children[i]->board->getField(j, k) = rand() % board_size + 1;
				}
			}
		}
	}
}

void GeneticSolver::performSuccession() {
	if (population[0]->score > children[0]->score) {
		delete population[0];
		population[0] = children[0];
	}
	for (unsigned i = 1; i < population_size; ++i) {
		delete population[i];
		population[i] = children[i];
	}
}

Individual* GeneticSolver::createChild(Individual* parent1, Individual* parent2) {
	unsigned size = parent1->board->getSize();
	Individual* child = new Individual(size);

	for (unsigned i = 0; i < size; ++i) {
		for (unsigned j = 0; j < size / 2; ++j) {
			child->board->getField(i, j) = parent1->board->getField(i, j);
		}

		for (unsigned j = size / 2; j < size; ++j) {
			child->board->getField(i, j) = parent2->board->getField(i, j);
		}
	}

	return child;
}

void GeneticSolver::print() {
	for (int i = 0; i < population_size; ++i) {
		cout << i << endl << *(population[i]->board) << endl
			<< "score: " << population[i]->score << endl
			<< "chances: " << probability[i].start << " " << probability[i].end << endl << endl;
	}
}

bool GeneticSolver::comp(Individual* in1, Individual* in2) {
	return in1->score < in2->score;
}

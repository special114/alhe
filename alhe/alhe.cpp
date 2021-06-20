#include <string>
#include <fstream>
#include "Board.h"
#include "Solver.h"
#include "TabuSolver.h"
#include "GeneticSolver.h"

using namespace std;

void readInputFile(unsigned& n, vector<vector<unsigned>>& constraints) {
	fstream file;
	file.open("input.txt", std::fstream::in);
	if (!file.is_open()) {
		cout << "Brak pliku input.txt";
		return;
	}

	char buffer[10];
	file.getline(buffer, 9);
	n = atoi(buffer);
	for (int i = 0; i < 4; ++i) {
		vector<unsigned> vec;
		for (int j = 0; j < n - 1; ++j) {
			file.getline(buffer, 9, ' ');
			vec.push_back(atoi(buffer));
		}
		file.getline(buffer, 9);
		vec.push_back(atoi(buffer));
		constraints.push_back(vec);
	}
}

int main( int argc, char* argv[] )
{
	if (argc == 1) {
		cout << "Podaj seed jako argument";
		return 0;
	}
	std::srand( atoi(argv[1]) );

	unsigned n;
	vector<vector<unsigned>> constraints;
	readInputFile(n, constraints);

	Board b(n);
	GeneticSolver g(b, 100, constraints);

	auto start = chrono::steady_clock::now();

	if (g.solve()) {
		auto end = chrono::steady_clock::now();
    chrono::duration<double> elapsed_seconds = end - start;

		cout << "Genetic:" << endl << b;
		cout << "elapsed time: " << elapsed_seconds.count() << "s\n";
	}

	cout << "\nTime for Tabu! \n";
	Board b2(n);
	TabuSolver s(b2, constraints);

  start = chrono::steady_clock::now();

	s.execute();

	auto end = chrono::steady_clock::now();
	chrono::duration<double> elapsed_seconds = end - start;
	
	cout << "We did it! \n";
	cout << b2 ;
	cout << "elapsed time: " << elapsed_seconds.count() << "s\n";
	return 0;
}
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
	for (int i = 0; i < n; ++i) {
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
	TabuSolver s(b, constraints);

	s.execute();

	cout << "Udalo sie! \n";
	cout << b ;
	return 0;
}
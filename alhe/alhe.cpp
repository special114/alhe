#include <string>

#include "Board.h"
#include "Solver.h"
#include "TabuSolver.h"
#include "GeneticSolver.h"

using namespace std;

int main()
{
	//std::srand(3123);

	unsigned n;
	cout << "Podaj rozmiar planszy: ";
	cin >> n;
	cin.ignore();
	Board b(n);
	TabuSolver s(b);

	s.top_constraints.push_back(0);
	s.top_constraints.push_back(2);
	s.top_constraints.push_back(5);
	s.top_constraints.push_back(0);
	s.top_constraints.push_back(0);
		//s.top_constraints.push_back(0);
		//s.top_constraints.push_back(0);
	s.left_constraints.push_back(2);
	s.left_constraints.push_back(0);
	s.left_constraints.push_back(0);
	s.left_constraints.push_back(0);
	s.left_constraints.push_back(3);
		//s.left_constraints.push_back(0);
		//s.left_constraints.push_back(0);
	//s.right_constraints.push_back(0);
	//s.right_constraints.push_back(0);
	//s.right_constraints.push_back(0);
	//s.right_constraints.push_back(0);
	//s.right_constraints.push_back(0);
	//s.bot_constraints.push_back(0);
	//s.bot_constraints.push_back(0);
	//s.bot_constraints.push_back(0);
	//s.bot_constraints.push_back(0);
	//s.bot_constraints.push_back(0);

	for (int i = 0; i < 5; ++i) {
		//s.top_constraints.push_back(0);
		s.bot_constraints.push_back(0);
		//s.left_constraints.push_back(0);
		s.right_constraints.push_back(0);
	}


	s.execute();

	cout << "we did it! \n";

	//b.getField(0, 0) = 1;
	//b.getField(0, 1) = 2;
	//b.getField(0, 2) = 3;
	//b.getField(1, 0) = 2;
	//b.getField(1, 1) = 3;
	//b.getField(1, 2) = 1;
	//b.getField(2, 0) = 3;
	//b.getField(2, 1) = 1;
	//b.getField(2, 2) = 2;

	cout << b ;
	//cout << s.isSolution(b);
}
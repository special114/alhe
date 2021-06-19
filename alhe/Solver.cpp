#include "Solver.h"

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

//vector<string> split(const string& s, char delimiter) {
//	vector<string> tokens;
//	string token;
//	//istringstream tokenStream(s);
//}

//bool Solver::isValidPosition(unsigned height, unsigned x, unsigned y) {
//	if( top_constraints[x] )
//	return true;
//}
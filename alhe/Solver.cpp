#include "Solver.h"

using namespace std;

unsigned Solver::getSize()
{
	return board.getSize();
}

Solver::Solver(Board& _board) : board(_board) {
	init();
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

vector<unsigned> Solver::split(const string& s, char delimiter) {
	vector<unsigned> tokens;
	string token;
	istringstream tokenStream(s);
	while (std::getline(tokenStream, token, delimiter)) {
		tokens.push_back(stoi(token));
	}
	return tokens;
}

//bool Solver::isValidPosition(unsigned height, unsigned x, unsigned y) {
//	if( top_constraints[x] )
//	return true;
//}
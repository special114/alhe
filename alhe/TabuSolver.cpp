#include "TabuSolver.h"
#include "random"

TabuSolver::TabuSolver(Board& _board) : Solver(_board) {}

void TabuSolver::randomInitialization()
{
    std::random_device rd; 
    std::mt19937 gen(rd()); 
    std::uniform_int_distribution<> distrib(1, getSize() );

}


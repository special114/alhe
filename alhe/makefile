CXX = g++
CXXFLAGS = -std=c++17

all: program

program: Board.cpp Solver.cpp TabuSolver.cpp GeneticSolver.cpp alhe.cpp
	$(CXX) Board.cpp Solver.cpp TabuSolver.cpp GeneticSolver.cpp alhe.cpp $(CXXFLAGS) -o program


clean:
	rm program

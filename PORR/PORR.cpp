// PORR.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"
#include "RandomUtils.h"
#include "FileLoader.h"
#include "PBPSOSolver.h"

using namespace std;

int main(int argc, char* argv[])
{
	if (argc < 2) {
		cout << "Usage:" << endl;
		cout << argv[0] << " <<filePath>>" << endl;
		cout << "filePath = path to problem file" << endl;
		return 0;
	}

	string filePath = argv[1];
	KnapsackProblem problem = FileLoader::load(filePath);

	cout << "Loaded file " << filePath << endl;
	cout << "Starting solver..." << endl;

	PBPSOSolver solver;
	solver.loadData(problem);
	solver.solve();

	cout << "Solving completed." << endl;
	cout << "Total profit: " << solver.getTotalProfit() << endl;

	return 0;
}
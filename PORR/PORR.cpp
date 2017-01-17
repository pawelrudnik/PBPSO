// PORR.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"
#include "RandomUtils.h"
#include "FileLoader.h"
#include "PBPSOSolver.h"
#include "Stopwatch.h"

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

	Stopwatch sw;
	sw.start();

	PBPSOSolver solver;
	solver.loadData(problem);
	solver.solve();

	sw.stop();

	cout << "Solving completed." << endl;
	cout.precision(10);
	cout << "Time elapsed: " << sw.elapsed() << endl;
	cout << "Total profit: " << solver.getTotalProfit() << endl;

	return 0;
}
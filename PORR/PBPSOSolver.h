#pragma once

#include "RandomUtils.h"
#include "KnapsackProblem.h"

using namespace std;

enum Mode {
	Sequential = 1,
	OpenMP = 2
};

class PBPSOSolver
{
	// Parametry algorytmu
	const int pop_size = 30;
	const int iterations = 100;
	const int maxTimesNotChanged = 10;
	const int R_min = -10;
	const int R_max = 10;
	const double omega = 0.8;
	const double c1 = 2.0;
	const double c2 = 2.0;

	// Dane wejœciowe
	int D = 0;
	int M = 0;
	vector<int> profits;
	vector<int> weights;

	// Dane wynikowe
	int totalProfit;
	int iterationsNumber;

	double velocity(double v_k, double x, double p_local, double p_global);
	double L(double x);
	bool toBinary(double x);
	int fitness(vector<bool> x);

public:

	void loadData(KnapsackProblem);
	void solve(Mode);
	int getTotalProfit();
	int getIterationsNumber();
};
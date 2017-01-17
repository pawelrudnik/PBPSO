#pragma once

#include "RandomUtils.h"
#include "KnapsackProblem.h"

using namespace std;

class PBPSOSolver
{
	// Parametry algorytmu
	int pop_size = 30;
	int iterations = 100;
	int R_min = -1;
	int R_max = 1;
	double omega = 0.8;
	double c1 = 2.0;
	double c2 = 2.0;

	// Dane wejœciowe
	int D = 0;
	int M = 0;
	vector<int> profits;
	vector<int> weights;

	// Dane wynikowe
	int totalProfit;

	double velocity(double v_k, double x, double p_local, double p_global);
	double L(double x);
	bool toBinary(double x);
	int fitness(vector<bool> x);

public:

	void loadData(KnapsackProblem);
	void solve();
	int getTotalProfit();
};
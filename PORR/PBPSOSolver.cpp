#include "stdafx.h"
#include "PBPSOSolver.h"

void PBPSOSolver::loadData(KnapsackProblem problem)
{
	D = problem.objectsCount;
	M = problem.knapsacksCapacities[0];
	profits = problem.objectsValues;
	weights = problem.constraints[0];
}

void PBPSOSolver::solve(Mode mode)
{
	// Struktury danych

	vector<vector<double>> x(pop_size, vector<double>(D, 0)); // pozycja
	vector<vector<double>> v(pop_size, vector<double>(D, 0)); // prêdkoœæ
	vector<vector<bool>> px(pop_size, vector<bool>(D, 0)); // wektory binarne
	vector<vector<bool>> best_px_local(pop_size, vector<bool>(D, 0)); // najlepsze wektory lokalne
	vector<bool> best_px_global(D); // najlepszy wektor globalny
	vector<int> best_fpx_local(pop_size); // najlepsze wyniki lokalne
	int best_fpx_global = 0; // najlepszy wynik globalny

	// Algorytm
	
	int fpx = 0;

	if (mode == Mode::Sequential) {

		for (int k = 0; k < iterations; k++) {
			for (int i = 0; i < pop_size; i++) {

				for (int j = 0; j < D; j++)
				{
					v[i][j] = velocity(v[i][j], x[i][j], best_px_local[i][j], best_px_global[j]);
					x[i][j] = x[i][j] + v[i][j];
					px[i][j] = toBinary(x[i][j]);
				}

				fpx = fitness(px[i]);

				if (fpx > best_fpx_local[i]) {
					best_px_local[i] = px[i];
					best_fpx_local[i] = fpx;

					if (fpx > best_fpx_global) {
						best_px_global = px[i];
						best_fpx_global = fpx;
					}
				}
			}
		}
	}
	else if(mode == Mode::OpenMP) {

		for (int k = 0; k < iterations; k++) {
			#pragma omp parallel num_threads(pop_size)
			{
				#pragma omp for
				for (int i = 0; i < pop_size; i++) {

					for (int j = 0; j < D; j++)
					{
						v[i][j] = velocity(v[i][j], x[i][j], best_px_local[i][j], best_px_global[j]);
						x[i][j] = x[i][j] + v[i][j];
						px[i][j] = toBinary(x[i][j]);
					}

					fpx = fitness(px[i]);

					if (fpx > best_fpx_local[i]) {
						best_px_local[i] = px[i];
						best_fpx_local[i] = fpx;

						if (fpx > best_fpx_global) {
							best_px_global = px[i];
							best_fpx_global = fpx;
						}
					}
				}
			}
		}

	}

	totalProfit = best_fpx_global;
}

int PBPSOSolver::getTotalProfit()
{
	return totalProfit;
}

double PBPSOSolver::velocity(double v_k, double x, double p_local, double p_global) {
	double r1 = randomDouble(0.0, 1.0);
	double r2 = randomDouble(0.0, 1.0);
	return omega * v_k + c1 * r1 * (p_local - x) + c2 * r2 * (p_global - x);
}

double PBPSOSolver::L(double x) {
	return (x - R_min) / (R_max - R_min);
}

bool PBPSOSolver::toBinary(double x) {
	return randomDouble(0.0, 1.0) <= L(x);
}

int PBPSOSolver::fitness(vector<bool> x)
{
	int total_profit = 0;
	int total_weight = 0;
	for (vector<bool>::size_type j = 0; j != x.size(); j++) {
		total_profit += profits[j] * x[j];
		total_weight += weights[j] * x[j];
	}
	return total_weight > M ? 0 : total_profit;
}
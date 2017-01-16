// PORR.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"
#include "RandomUtils.h"

using namespace std;

const int pop_size = 10;
const int D = 4;
const int iterations = 10;
const int R_min = -1;
const int R_max = 1;
const double omega = 0.8;
const double c1 = 2.0;
const double c2 = 2.0;
const int profit[D] = { 4, 5, 3, 2 };
const int weight[D] = { 1, 2, 3, 2 };
const int M = 6;

double velocity(double v_k, double x, double p_local, double p_global) {
	double r1 = randomDouble(0.0, 1.0);
	double r2 = randomDouble(0.0, 1.0);
	return omega * v_k + c1 * r1 * (p_local - x) + c2 * r2 * (p_global - x);
}

double L(double x) {
	return (x - R_min) / (R_max - R_min);
}

bool binary(double x) {
	return randomDouble(0.0, 1.0) <= L(x);
}

int fitness(bool x[])
{
	int total_profit = 0;
	int total_weight = 0;
	for (int j = 0; j < D; j++) {
		total_profit += profit[j] * x[j];
		total_weight += weight[j] * x[j];
	}
	return total_weight > M ? 0 : total_profit;
}

void CopyBoolArray(bool dest[], bool target[]) {
	for (int i = 0; i < D; i++) {
		target[i] = dest[i];
	}
}

int main()
{
	double x[pop_size][D]; // pozycja
	double v[pop_size][D]; // prêdkoœæ
	bool px[pop_size][D]; // wektory binarne
	bool best_px_local[pop_size][D]; // najlepsze wektory lokalne
	bool best_px_global[D]; // najlepszy wektor globalny
	int best_fpx_local[pop_size]; // najlepsze wyniki lokalne
	int best_fpx_global; // najlepszy wynik globalny

	// Inicjalizacja wartoœci
	for (int i = 0; i < pop_size; i++) {
		for (int j = 0; j < D; j++) {
			x[i][j] = randomInt(1, 10);
			v[i][j] = 0;
			px[i][j] = 0;
			best_px_local[i][j] = 0;
			best_px_global[j] = 0;
		}
		best_fpx_local[i] = 0;
	}
	best_fpx_global = 0;

	// Algorytm
	double fpx = 0;
	for (int k = 0; k < iterations; k++) {
		for (int i = 0; i < pop_size; i++) {

			for (int j = 0; j < D; j++)
			{
				v[i][j] = velocity(v[i][j], x[i][j], best_px_local[i][j], best_px_global[j]);
				x[i][j] = x[i][j] + v[i][j];
				px[i][j] = binary(x[i][j]);
			}
			 
			fpx = fitness(px[i]);

			if (fpx > best_fpx_local[i]) {
				CopyBoolArray(px[i], best_px_local[i]);
				best_fpx_local[i] = fpx;

				if (fpx > best_fpx_global) {
					CopyBoolArray(px[i], best_px_global);
					best_fpx_global = fpx;
				}
			}
		}
	}

	cout << best_fpx_global << endl;

	system("PAUSE");
	return 0;
}

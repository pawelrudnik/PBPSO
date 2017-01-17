// PORR.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"
#include "RandomUtils.h"
#include "FileLoader.h"

using namespace std;

// Parametry algorytmu
const int pop_size = 30;
const int iterations = 100;
const int R_min = -1;
const int R_max = 1;
const double omega = 0.8;
const double c1 = 2.0;
const double c2 = 2.0;

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

int fitness(vector<bool> x, vector<int> profits, vector<int> weights, int M)
{
	int total_profit = 0;
	int total_weight = 0;
	for (vector<bool>::size_type j = 0; j != x.size(); j++) {
		total_profit += profits[j] * x[j];
		total_weight += weights[j] * x[j];
	}
	return total_weight > M ? 0 : total_profit;
}

int main(int argc, char* argv[])
{
	if (argc < 2) {
		cout << "Usage:" << endl;
		cout << argv[0] << " <<filePath>>" << endl;
		cout << "filePath = path to problem file" << endl;
		return 0;
	}

	string filePath = argv[1];
	FileInfo fileInfo = FileLoader::load(filePath);

	int D = fileInfo.objectsCount;

	vector<int> profits = fileInfo.objectsValues;
	vector<int> weights = fileInfo.constraints[0];
	int M = fileInfo.knapsacksCapacities[0];



	// Struktury danych
	vector<vector<double>> x(pop_size, vector<double>(D, 0)); // pozycja
	vector<vector<double>> v(pop_size, vector<double>(D, 0)); // prêdkoœæ
	vector<vector<bool>> px( pop_size, vector<bool>(D, 0) ); // wektory binarne
	vector<vector<bool>> best_px_local(pop_size, vector<bool>(D, 0)); // najlepsze wektory lokalne
	vector<bool> best_px_global(D); // najlepszy wektor globalny
	vector<int> best_fpx_local(pop_size); // najlepsze wyniki lokalne
	int best_fpx_global = 0; // najlepszy wynik globalny



	// Algorytm
	int fpx = 0;
	for (int k = 0; k < iterations; k++) {
		for (int i = 0; i < pop_size; i++) {

			for (int j = 0; j < D; j++)
			{
				v[i][j] = velocity(v[i][j], x[i][j], best_px_local[i][j], best_px_global[j]);
				x[i][j] = x[i][j] + v[i][j];
				px[i][j] = binary(x[i][j]);
			}
			 
			fpx = fitness(px[i], profits, weights, M);

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



	cout << "Result vector: [ ";
	for (vector<bool>::size_type j = 0; j != best_px_global.size(); j++) {
		cout << best_px_global[j] << " ";
	}
	cout << "]\n";
	cout << "Total profit: " << best_fpx_global << endl;

	return 0;
}

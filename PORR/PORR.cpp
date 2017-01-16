// PORR.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"
#include "RandomUtils.h"

using namespace std;

const int pop_size = 10;
const int D = 2;
const int iterations = 100;
const int R_min = -1;
const int R_max = 1;
const double omega = 0.8;
const double c1 = 2.0;
const double c2 = 2.0;
const int profit[D] = { 4, 5 };

double velocity(double v_k, double x, double p_local, double p_global) {
	return omega * v_k + c1 * (p_local - x) + c2 * (p_global - x);
}

double L(double x) {
	return (x - R_min) / (R_max - R_min);
}

bool binary(double x) {
	return randomNumber(0.0, 1.0) <= L(x);
}

double fitness(bool x[])
{
	double result = 0;
	for (int j = 0; j < D; j++) {
		result += (double)profit[j] * x[j];
	}
	return result;
}

int main()
{
	double x[pop_size][D]; // pozycja
	double v[pop_size][D]; // prêdkoœæ
	bool px[pop_size][D]; // wynik binarny 
	double p_local[pop_size][D]; // najlepsze wyniki lokalne
	double p_global[D]; // najlepszy wynik globalny

	// Inicjalizja wartoœci
	for (int i = 0; i < pop_size; i++) {
		for (int j = 0; j < D; j++) {
			x[i][j] = 0;
			v[i][j] = 0;
			px[i][j] = 0;
			p_local[i][j] = 0;
			p_global[j] = 0;
		}
	}

	// Algorytm
	for (int k = 0; k < iterations; k++) {
		for (int i = 0; i < pop_size; i++) {

			for (int j = 0; j < D; j++)
			{
				v[i][j] = velocity(v[i][j], x[i][j], p_local[i][j], p_global[j]);
				x[i][j] = x[i][j] + v[i][j];
				px[i][j] = binary(x[i][j]);
			}

			//if (fitness(px[i]) > fitness(p_local[i])) {
			//	p_local[i] = x[i];

			//	if (fitness(px[i]) > fitness(p_global)) {
			//		p_global = x[i];
			//	}
			//}
		}
	}

	system("PAUSE");
	return 0;
}

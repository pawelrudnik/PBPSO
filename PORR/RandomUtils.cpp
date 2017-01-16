#include "RandomUtils.h"
#include "stdafx.h"
#include <random>

double randomDouble(double lower_bound, double upper_bound) {
	std::uniform_real_distribution<double> unif(lower_bound, upper_bound);
	std::random_device rd;
	std::mt19937 gen(rd());
	return unif(gen);
}

int randomInt(int lower_bound, int upper_bound) {
	std::uniform_int_distribution<int> unif(lower_bound, upper_bound);
	std::random_device rd;
	std::mt19937 gen(rd());
	return unif(gen);
}
#include "RandomUtils.h"
#include "stdafx.h"
#include <random>

double randomDouble(double lower_bound, double upper_bound) {
	std::uniform_real_distribution<double> unif(lower_bound, upper_bound);
	std::default_random_engine re;
	return unif(re);
}
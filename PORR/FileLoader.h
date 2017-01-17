#pragma once

#include <fstream>
#include <sstream>
#include "KnapsackProblem.h"

using namespace std;

class FileLoader
{
	static int nextInt(fstream &f);
	static void nextInts(fstream& f, vector<int> &dst, int limit);
	static string nextToken(fstream& f);
	static void skipLine(fstream &f);

public:
	static KnapsackProblem load(string fileName);
};
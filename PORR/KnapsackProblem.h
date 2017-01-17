#pragma once

using namespace std;

struct KnapsackProblem
{
	int knapsacksCount;
	int objectsCount;
	int optimum;
	vector<int> objectsValues;
	vector<int> knapsacksCapacities;
	vector<vector<int>> constraints;
	string nameOfTheGame = "";
};
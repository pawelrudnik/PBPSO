#pragma once

using namespace std;

struct FileInfo
{
	int knapsacksCount;
	int objectsCount;
	vector<int> objectsValues;
	vector<int> knapsacksCapacities;
	vector<vector<int>> constraints;
	string nameOfTheGame = "";
};
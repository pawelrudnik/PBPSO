#pragma once

#include <fstream>
#include <sstream>
#include "FileInfo.h"

using namespace std;

class FileLoader
{
	static int nextInt(fstream &f);
	static void nextInts(fstream& f, vector<int> &dst, int limit);
	static string nextToken(fstream& f);
	static void skipLine(fstream &f);

public:
	static FileInfo load(string fileName);
};
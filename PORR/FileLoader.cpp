#include "stdafx.h"
#include "FileLoader.h"


KnapsackProblem FileLoader::load(string fileName)
{
	fstream file;

	file.open(fileName);
	if (!file.is_open()) {
		throw std::runtime_error("Couldn't open file " + fileName + " for reading");
	}

	KnapsackProblem fileInfo;
	fileInfo.knapsacksCount = nextInt(file);
	fileInfo.objectsCount = nextInt(file);
	nextInts(file, fileInfo.objectsValues, fileInfo.objectsCount);
	nextInts(file, fileInfo.knapsacksCapacities, fileInfo.knapsacksCount);
	for (int i = 0; i < fileInfo.knapsacksCount; ++i) {
		vector<int> constraints;
		nextInts(file, constraints, fileInfo.objectsCount);
		fileInfo.constraints.push_back(constraints);
	}

	fileInfo.optimum = nextInt(file);
	fileInfo.nameOfTheGame = nextToken(file);

	return fileInfo;
}

int FileLoader::nextInt(fstream &f) {
	return atoi(nextToken(f).c_str());
}

void FileLoader::nextInts(fstream& f, vector<int> &dst, int limit) {
	int i = 0;
	while (i < limit) {
		dst.push_back(nextInt(f));
		i++;
	}
}

string FileLoader::nextToken(fstream& f) {

	if (f.eof()) {
		return "";
	}

	string token;
	f >> token;
	if (token[0] == '/') {
		skipLine(f);
		return nextToken(f);
	}

	return token;
}

void FileLoader::skipLine(fstream &f) {
	int c;
	while (((c = f.get()) != '\n') && c != '\r');
}

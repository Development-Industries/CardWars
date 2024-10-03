#pragma once
#include <vector>
#include "ResultsLib.h"
class Tester
{
public:
	const char* file;
	Tester() : file("..\\..\\CardWars\\CardWars.results")
	{
		std::vector<const char*> codeFiles{ "CardWars.cpp", "WarGame.h", "WarGame.cpp" };
		results::WriteResults(codeFiles, file);
	}

	void ShowResults()
	{
		results::ReadResults(file, std::chrono::seconds(900));
	}
};


#pragma once

#include <vector>
#include <string>

extern std::vector<std::vector<std::string>> funcStorage;
int funcIndex = -1;
int addToFunc(std::string line)
{
	funcStorage[funcIndex].push_back(line);
	return 1;
}

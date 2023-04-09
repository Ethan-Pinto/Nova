#pragma once

extern int lineNum;
int error()
{
	std::cout << "ERROR: Line " << lineNum << ", unknown syntax/sequence" << std::endl;
	return -1;
}

int detailedError(std::string msg)
{
	std::cout << "ERROR: Line " << lineNum << ", " << msg << std::endl;
	return -1;
}

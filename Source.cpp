#include <iostream>
#include <fstream>
#include <map>
#include <chrono>

#include "ProcessLine.h"

/*
    RETURN VALUE MEANINGS

    * 2 = start of function
    * 1 = success
    * 0 = neutral (neither error or success)
    * -1 = error
    * -2 = expel
    *
*/

int lineNum = 0;
const int MAX_LINE_LENGTH = 1024;

std::vector<std::vector<std::string>> funcStorage = {};

int funcIndex = -1;
int main(int argc, char* argv[])
{
    if (!argv[1]) return -1;

    system("title Nova");

    std::ifstream file(argv[1]);
    char line[MAX_LINE_LENGTH];

    int result = 1;
    bool isFunc = false;

    auto start = std::chrono::high_resolution_clock::now();
    while (file.getline(line, MAX_LINE_LENGTH))
    {
        lineNum++;
        if (removeSpaces(line) == "end") {
            isFunc = false;
            continue;
        }

        if (strlen(line) == 0) {
            continue;
        }

        if (isFunc == true) {
            funcStorage[funcIndex].push_back(line);
            continue;
        }
        else {
            result = processLine(line);
        }

        if (result == -1 || result == -2) break;

        if (result == 2) {
            isFunc = true;
            funcIndex++;
        }
    }

    std::map<int, std::string> messages = {
        {-1, "Code interpretation failed."},
        {-2, "Code interpretation expelled."},
        {1, "Code interpretation success!"},
    };

    auto end = std::chrono::high_resolution_clock::now();
    auto elapsed_time = std::chrono::duration_cast<std::chrono::milliseconds>(end - start).count();

    std::cout << messages[result] << " Time taken: " << elapsed_time << "ms" << std::endl;
    system("pause");

    return result == 0 ? 1 : -1;
}

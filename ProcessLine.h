#pragma once

#include <map>
#include <string>

#include "TokenFunctions.h"
#include "Error.h"

extern int lineNum;

std::map<std::string, int (*)(std::string, std::string, size_t)> functionMap = {
    {"print", &PrintToken},
    {"warn", &WarnToken},
    {"expel()", &ExpelToken},
    {"suspend()", &SuspendToken},
    {"def", &DefToken},
    {"func", &funcToken},
    {"call", &callFunc}
};

std::string removeSpaces(std::string line) {
    bool insideQuotes = false;
    int writePos = 0;

    for (int i = 0; line[i] != '\0'; i++) {
        if (line[i] == '\"') {
            insideQuotes = !insideQuotes;
        }
        else if ((line[i] == ' ' || line[i] == '\t') && !insideQuotes) {
            continue;
        }
        line[writePos] = line[i];
        writePos++;
    }

    line[writePos] = '\0';

    return std::string(line);
}

int processLine(std::string strLine)
{
    for (const auto& functionPair : functionMap) {
        const std::string& token = functionPair.first;

        size_t pos = strLine.find(token);
        if (pos != std::string::npos) {
            size_t quote1 = strLine.rfind('\"', pos);
            size_t quote2 = strLine.find('\"', pos);
            if (quote1 != std::string::npos && quote2 != std::string::npos && quote1 < pos && quote2 > pos) {
                break;
            }

            return functionPair.second(removeSpaces(strLine), token, pos);
        }
    }

    return error();
}

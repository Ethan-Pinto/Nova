#pragma once
#include <iostream>
#include <vector>

#include "Error.h"
#include "ProcessLine.h"

extern int lineNum;

std::vector<std::pair<std::string, double>> numVariables;
std::vector<std::pair<std::string, std::string>> stringVariables;
extern std::vector<std::vector<std::string>> funcStorage;

int PrintToken(std::string line, std::string token, size_t pos)
{
    size_t firstQuotePos = line.find('"', pos);
    size_t secondQuotePos = line.find('"', firstQuotePos + 1);
    std::string textBetweenQuotes;

    if (firstQuotePos != std::string::npos && secondQuotePos != std::string::npos) {
        std::cout << line.substr(firstQuotePos + 1, secondQuotePos - firstQuotePos - 1) << std::endl;
        return 1;
    }

    std::string variableName = line.substr(token.length());
    for (const auto& pair : numVariables) {
        if (pair.first == variableName) {
            std::cout << pair.second << std::endl;
            return 1;
        }
    }

    for (const auto& pair : stringVariables) {
        if (pair.first == variableName) {
            std::cout << pair.second << std::endl;
            return 1;
        }
    }

    return error();
}

int WarnToken(std::string line, std::string token, size_t pos)
{
    std::cout << "(" + std::to_string(lineNum) + ") WARN: ";
    PrintToken(line, token, pos);

    return 1;
}

int ExpelToken(std::string line, std::string token, size_t pos)
{
    return -2;
}

int SuspendToken(std::string line, std::string token, size_t pos)
{
    std::cout << "Code interpretation suspended. Type 1 to continue, or -1 to expel." << std::endl;

    int input;
    std::cin >> input;

    if (input == -1) {
        return -2;
    }
    else if (input == 1) {
        return 1;
    }
    else {
        return detailedError("Unknown input on pause function.");
    }
}

int DefToken(std::string line, std::string token, size_t pos)
{
    size_t signPos = line.find('=');

    if (signPos == std::string::npos) return detailedError("Missing equality operator");

    size_t firstQuotePos = line.find('"', signPos + 1);
    size_t secondQuotePos = line.find('"', firstQuotePos + 1);

    std::string variableName = line.substr(pos + token.length(), signPos - pos - token.length());

    if (firstQuotePos != std::string::npos && secondQuotePos != std::string::npos) {
        std::string quotedText = line.substr(firstQuotePos + 1, secondQuotePos - firstQuotePos - 1);
        stringVariables.push_back(std::make_pair(variableName, quotedText));

        return 1;
    }
    else if (firstQuotePos == std::string::npos && secondQuotePos == std::string::npos) {
        std::string value = line.substr(signPos + 1);

        try {
            double number = std::stod(value);
            numVariables.push_back(std::make_pair(variableName, number));

            return 1;
        }
        catch (...) {
            return detailedError("Missing or incorrect quotation marks");
        }
    }
    else {
        return detailedError("Incorrect/missing quotations");
    }

    return 0;
}

int funcToken(std::string line, std::string token, size_t pos)
{
    size_t start = line.find(token, pos);

    size_t end = line.find("(", token.length());
    if (end == std::string::npos)
        return detailedError("missing opening bracket '('");

    size_t closing_bracket_pos = line.find(")", end + 1);
    if (closing_bracket_pos == std::string::npos)
        return detailedError("missing closing bracket ')'");

    std::string result = line.substr(start + token.length(), -4);

    size_t end_pos = result.find("(");
    if (end_pos != std::string::npos) {
        result = result.substr(0, end_pos);
    }

    for (const auto& inner_vector : funcStorage) {
        if (!inner_vector.empty() && inner_vector[0] != result)
            continue;
        return detailedError("function name already in use!");
    }

    funcStorage.push_back({ result });

    return 2;
}

extern std::map<std::string, int (*)(std::string, std::string, size_t)> functionMap;
extern int funcIndex;
int callFunc(std::string line, std::string token, size_t pos)
{
    size_t open = line.find('(');
    if (open == std::string::npos)
    {
        return detailedError("missing opening bracket '('");
    }

    size_t close = line.find(')', open + 1);
    if (close == std::string::npos)
    {
        return detailedError("missing closing bracket ')'");
    }

    std::string sub = line.substr(open + 1, close - open - 1);

    for (auto func : funcStorage) {
        if (func[0] == sub.substr(0, sub.length() - 1)) {
            for (int i = 1; i < func.size(); i++) {
                std::string strLine = func[i];

                for (const auto& functionPair : functionMap) {
                    const std::string& new_token = functionPair.first;

                    size_t new_pos = strLine.find(new_token);
                    functionPair.second(strLine, new_token, new_pos);
                }
            }
            return 1;
        }
    }

    return detailedError("couldn't find function name");
}

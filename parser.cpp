#include "parser.h"
#include <iostream>
#include <fstream>
#include <string>
#include <vector>

std::string Parser::trim(const std::string s)
{
    std::string trimmed = "";
    int start = 0;
    while (s[start] == ' ')
    { // Find end of whitespaces in the start
        start++;
    }

    int end = s.length() - 1;
    while (s[end] == ' ')
    { // Find start of whitespaces in the end
        end--;
    }

    for (int i = start; i <= end; i++)
    {
        trimmed += s[i];
    }

    return trimmed;
}

int Parser::stringToInt(const std::string number)
{
    if (number.length() == 1)
    { // If there is only one digit, subtract 48 from the ASCII code
        return (number[0] - 48);
    }
    else
    {
        int converted = 0;
        if (number[0] == '-')
        {
            for (int i = 1; i < number.length(); i++)
            {
                converted = (number[i] - 48) + 10 * converted;
            }
            converted *= -1;
        }
        else
        {
            for (int i = 0; i < number.length(); i++)
            {
                converted = (number[i] - 48) + 10 * converted;
            }
        }
        return converted;
    }
}

void Parser::processProblemLine(std::string line, int &n_vars, int &n_clauses)
{
    // Problem line
    // p cnf <n_vars> <n_clauses>
    std::string token = "";
    int tokenNumber = 1;
    for (int j = 0; j < line.length(); j++)
    {
        if (line[j] == ' ')
        {
            if (tokenNumber == 3)
            {
                n_vars = stringToInt(token);
            }
            tokenNumber++;
            token = "";
        }
        else
        {
            token += line[j];
        }
    }
    n_clauses = stringToInt(token);
}

void Parser::processClauseLine(std::string line)
{
    std::string number = "";
    std::vector <int> clause;
    for (int j = 0; j < line.length(); j++)
    {
        if (line[j] == ' ')
        {
            clause.push_back(stringToInt(number));
            number = "";
        }
        else
        {
            number += line[j];
        }
    }
    clauses.push_back(clause);
}

Parser::Parser(std::string path)
{
    n_vars = n_clauses = 0;
    std::string line;
    std::ifstream dimacs(path);
    if (dimacs.is_open())
    {
        while (getline(dimacs, line))
        {
            line = trim(line);
            if (line.length() == 0)
            {
                // Line consists of whitespaces only
            }
            else
            {
                if (line[0] == 'c')
                {
                    // Comment lines which can be ignored
                }
                else if (line[0] == 'p')
                {
                    processProblemLine(line, n_vars, n_clauses);
                }
                else
                {
                    processClauseLine(line);
                }
            }
        }
        dimacs.close();
    }
    else
    {
        std::cout << "Unable to read the SAT problem.\n";
    }
}

int Parser::getNumberOfClauses() 
{
    return n_clauses;
}

int Parser::getNumberOfVariables() 
{
    return n_vars;
}

void Parser::printClauses()
{
    for (int i = 0; i < n_clauses; i++)
    {
        for (auto x : clauses[i])
        {
            std::cout << x << " ";
        }
        std::cout << "\n";
    }
}

/*
int main(int argc, char **argv)
{
    Parser parser(argv[1]);
    std::cout << "Number of variables: " << parser.getNumberOfVariables() << "\n";
    std::cout << "Number of clauses: " << parser.getNumberOfClauses() << "\n";
    parser.printClauses();
}
*/

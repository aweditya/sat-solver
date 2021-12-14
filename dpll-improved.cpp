#include "parser.h"
#include <algorithm>
#include <iostream>
#include <vector>

void printClauses(std::vector<std::vector<int>> clauses)
{
    for (int i = 0; i < clauses.size(); i++)
    {
        for (auto x : clauses[i])
        {
            std::cout << x << " ";
        }
        std::cout << "\n";
    }
}

std::vector<std::vector<int>> copyClauses(std::vector<std::vector<int>> clauses)
{
    std::vector<std::vector<int>> copy;
    for (int i = 0; i < clauses.size(); i++)
    {
        copy.push_back(clauses[i]);
    }
    return copy;
}

bool checkConsistency(std::vector<std::vector<int>> clauses)
{
    return clauses.size() == 0;
}

bool containsEmptyClause(std::vector<std::vector<int>> clauses)
{
    for (int i = 0; i < clauses.size(); i++)
    {
        if (clauses[i].size() == 0)
        {
            return true;
        }
    }
    return false;
}

int findLiteralInClause(int literal, std::vector<int> clause, bool &literalPolarity)
{
    for (int i = 0; i < clause.size(); i++)
    {
        if (clause[i] == literal)
        {
            literalPolarity = true;
            return i;
        }
        else if (clause[i] == -literal)
        {
            literalPolarity = false;
            return i;
        }
    }
    return -1;
}

void updateClauses(int literal, bool literalAssignment, std::vector<std::vector<int>> &clauses)
{
    for (int i = 0; i < clauses.size(); i++)
    {
        bool literalPolarity = false;
        int index = findLiteralInClause(literal, clauses[i], literalPolarity);
        if (index != -1)
        {
            if (literalPolarity)
            {
                if (literalAssignment)
                {
                    clauses.erase(clauses.begin() + i);
                    i--;
                }
                else
                {
                    clauses[i].erase(clauses[i].begin() + index);
                }
            }
            else
            {
                if (!literalAssignment)
                {
                    clauses.erase(clauses.begin() + i);
                    i--;
                }
                else
                {
                    clauses[i].erase(clauses[i].begin() + index);
                }
            }
        }
    }
}

int checkUnitClause(std::vector<int> clause)
{
    if (clause.size() == 1)
    {
        return clause[0];
    }
    else
    {
        return 0;
    }
}

void unitPropagate(int literal, bool literalAssignment, std::vector<std::vector<int>> &clauses)
{
    updateClauses(literal, literalAssignment, clauses);
}

int checkPureLiteral(int literal, std::vector<std::vector<int>> clauses)
{
    int pos = 0, neg = 0;
    for (int i = 0; i < clauses.size(); i++)
    {
        bool literalPolarity = false;
        int index = findLiteralInClause(literal, clauses[i], literalPolarity);
        if (index != -1)
        {
            if (literalPolarity)
            {
                pos++;
            }
            else
            {
                neg++;
            }
        }
    }
    if (pos == 0 && neg == 0)
    {
        return 0;
    }
    else if (pos == 0)
    {
        return -1;
    }
    else if (neg == 0)
    {
        return 1;
    }
    else
    {
        return 0;
    }
}

void pureLiteralAssign(int literal, bool literalAssignment, std::vector<std::vector<int>> &clauses)
{
    updateClauses(literal, literalAssignment, clauses);
}

int chooseLiteral(int n_vars, std::vector<int> &usedLiterals)
{
    for (int i = 1; i <= n_vars; i++)
    {
        if (std::find(usedLiterals.begin(), usedLiterals.end(), i) == usedLiterals.end())
        {
            return i;
        }
    }
    return -1;
}

bool SAT(std::vector<std::vector<int>> clauses, int n_vars, std::vector<int> &usedLiterals)
{
    if (checkConsistency(clauses))
    {
        return true;
    }
    else if (containsEmptyClause(clauses))
    {
        return false;
    }
    else
    {
        for (int i = 0; i < clauses.size(); i++)
        {
            int unitLiteral = checkUnitClause(clauses[i]);
            if (unitLiteral > 0)
            {
                unitPropagate(unitLiteral, true, clauses);
                usedLiterals.push_back(unitLiteral);
            }
            else if (unitLiteral < 0)
            {
                unitPropagate(unitLiteral, false, clauses);
                usedLiterals.push_back(-unitLiteral);

            }
        }
        for (int i = 1; i <= n_vars; i++)
        {
            int pureLiteralPolarity = checkPureLiteral(i, clauses);

            if (pureLiteralPolarity > 0)
            {
                pureLiteralAssign(i, true, clauses);
                usedLiterals.push_back(i);
            }
            else if (pureLiteralPolarity < 0)
            {

                pureLiteralAssign(i, false, clauses);
                usedLiterals.push_back(i);

            }
        }
        std::vector<std::vector<int>> clausesCopy = copyClauses(clauses);
        std::vector<int> usedLiteralsCopy = usedLiterals;

        int chosenLiteral = chooseLiteral(n_vars, usedLiterals);
        if (chosenLiteral != -1)
        {
            usedLiterals.push_back(chosenLiteral);
            updateClauses(chosenLiteral, true, clauses);
        }
        bool checkSATWith1 = SAT(clauses, n_vars, usedLiterals);
        if (chosenLiteral != -1)
        {
            usedLiteralsCopy.push_back(chosenLiteral);
            updateClauses(chosenLiteral, false, clausesCopy);
        }
        bool checkSATWith0 = SAT(clausesCopy, n_vars, usedLiteralsCopy);

        return checkSATWith1 | checkSATWith0;
    }
}

int main(int argc, char **argv)
{
    if (argc == 1)
    {
        std::cout << "No SAT problem provided.\n";
    }
    else if (argc > 2)
    {
        std::cout << "Too many problems provided.\n";
    }
    else
    {
        Parser parser(argv[1]);
        int n_clauses = parser.getNumberOfClauses();
        int n_vars = parser.getNumberOfVariables();
        std::vector<std::vector<int>> clauses = parser.clauses;
        std::vector<int> usedLiterals;
        std::cout << SAT(clauses, n_vars, usedLiterals) << "\n";
    }
}
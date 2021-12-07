#include "parser.h"
#include <iostream>
#include <vector>

std::vector<std::vector<int>> copyMatrix(std::vector<std::vector<int>> matrix, int rows, int cols)
{
    std::vector<std::vector<int>> copy(rows, std::vector<int>(cols, 0));
    for (int i = 0; i < rows; i++)
    {
        for (int j = 0; j < cols; j++)
        {
            copy[i][j] = matrix[i][j];
        }
    }
    return copy;
}

std::vector<std::vector<int>> convertClausetoSATMatrix(std::vector<std::vector<int>> clauses, int n_clauses, int n_vars)
{
    std::vector<std::vector<int>> matrix(n_clauses, std::vector<int>(n_vars + 1, 0));
    for (int i = 0; i < n_clauses; i++)
    {
        for (int j = 0; j < clauses[i].size(); j++)
        {
            if (clauses[i][j] > 0)
            {
                matrix[i][clauses[i][j] - 1] = 1;
            }
            else
            {
                matrix[i][-clauses[i][j] - 1] = -1;
            }
        }
    }
    return matrix;
}

/*
    Matrix clauses is of dimension (num_clauses) x (num_var + 1)
    Each entry in the matrix upto column (num_var - 1) takes the
    values 1, 0, -1. 1 indicates that the variable is present in
    the clause in an uncomplemented form while -1 indicates that
    the variable is complemented. 0 indicates the absence of the
    variable in the clause.
    The final column is to check if the clause has been satisfied.
    In the last level of recursion i.e. when all variables have
    been assigned a value, we check this column to determine SAT.
*/
bool SAT(std::vector<std::vector<int>> clauses, int n_clauses, int n_vars, int current_var, std::vector<int> &testAssignment, std::vector<int> &solution)
{
    if (current_var == n_vars)
    {
        for (int i = 0; i < n_clauses; i++)
        {
            if (clauses[i][n_vars] == 0)
            { // The problem is UNSAT
                return false;
            }
        }
        // If all clauses have been satisfied, we have SAT
        for (int i = 0; i < n_vars; i++)
        {
            solution[i] = testAssignment[i];
        }
        return true;
    }
    else
    {
        // Make a copy of the SAT matrix to test for both cases
        std::vector<std::vector<int>> clausesCopy = copyMatrix(clauses, n_clauses, n_vars + 1);

        /*
            First assign 1 to current_var. If the clause has already
            been satisfied, skip it. If it hasn't check if the variable
            is present in the clause or not. If it is present and
            uncomplemented, set the SAT bit to 1. Else, leave it as it is.
        */
        testAssignment[current_var] = 1;

        for (int i = 0; i < n_clauses; i++)
        { // current_var is assigned 1
            if (clauses[i][n_vars] == 0)
            { // check if the clause is already satisfied
                if (clauses[i][current_var] == 1)
                { // if the variable is uncomplemented, the clause is satisfied
                    clauses[i][n_vars] = 1;
                }
            }
        }

        bool checkSATWith1 = SAT(clauses, n_clauses, n_vars, current_var + 1, testAssignment, solution);

        testAssignment[current_var] = 0;
        for (int i = 0; i < n_clauses; i++)
        { // current_var is assigned 0
            if (clausesCopy[i][n_vars] == 0)
            { // check if the clause is already satisfied
                if (clausesCopy[i][current_var] == -1)
                { // if the variable is complemented, the clause is satisfied
                    clausesCopy[i][n_vars] = 1;
                }
            }
        }

        bool checkSATWith0 = SAT(clausesCopy, n_clauses, n_vars, current_var + 1, testAssignment, solution);
        return (checkSATWith0 | checkSATWith1);
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
        std::vector<std::vector<int>> matrix = convertClausetoSATMatrix(clauses, n_clauses, n_vars);
        std::vector<int> testAssignment(n_vars, 1);
        std::vector<int> solution(n_vars, 1);

        bool sat = SAT(matrix, n_clauses, n_vars, 0, testAssignment, solution);
        if (sat)
        {
            std::cout << "SAT\n";
            for (auto assignment : solution)
            {
                std::cout << assignment << " ";
            }
            std::cout << "\n";
        }
        else
        {
            std::cout << "UNSAT \n";
        }
    }
}
#include <iostream>
#include <vector>

using namespace std;

bool SAT(vector < vector<int> > clauses, int num_clauses, int num_var, int current_var)
{
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
    if (current_var == num_var)
    {
        for (int i = 0; i < num_clauses; i++)
        {
            if (clauses[i][num_var] == 0)
            { // The problem is UNSAT
                return false;
            }
        }
        // If all clauses have been satisfied, we have SAT
        return true;
    }
    else
    {
        /*
            First assign 1 to current_var. If the clause has already
            been satisfied, skip it. If it hasn't check if the variable
            is present in the clause or not. If it is present and 
            uncomplemented, set the SAT bit to 1. Else, leave it as it is.
        */
        for (int i = 0; i < num_clauses; i++)
        { // current_var is assigned 1
            if (clauses[i][num_var] == 0)
            { // check if the clause is already satisfied
                if (clauses[i][current_var] == 1)
                { // if the variable is uncomplemented, the clause is satisfied
                    clauses[i][num_var] = 1;
                }
            }
        }
        bool checkSATWith1 = SAT(clauses, num_clauses, num_var, current_var + 1);

        for (int i = 0; i < num_clauses; i++)
        { // current_var is assigned 0
            if (clauses[i][num_var] == 0)
            { // check if the clause is already satisfied
                if (clauses[i][current_var] == -1)
                { // if the variable is complemented, the clause is satisfied
                    clauses[i][num_var] = 1;
                }
            }
        }
        bool checkSATWith0 = SAT(clauses, num_clauses, num_var, current_var + 1);
        return (checkSATWith0 | checkSATWith1);
    }
}

int main()
{
    int num_clauses = 2, num_var = 1;
    vector < vector<int> > clauses = {
        {1, 0}, 
        {1, 0}
    };
    for (int i = 0; i < num_clauses; i++) 
    {
        for (int j = 0; j < num_var + 1; j++) 
        {
            cout << clauses[i][j] << " ";
        }
        cout << "\n";
    }
    cout << SAT(clauses, num_clauses, num_var, 0) << "\n";
    return 0;
}
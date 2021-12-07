# ifndef _PARSER_
# define _PARSER_

#include <vector>
#include <string>

class Parser
{
private:
    int n_vars, n_clauses;
    
    std::string trim(const std::string s);
    int stringToInt(const std::string number);
    void processProblemLine(std::string line, int &n_vars, int &n_clauses);
    void processClauseLine(std::string line);
    
public:
    std::vector<std::vector<int>> clauses;

    Parser(std::string path);
    int getNumberOfClauses();
    int getNumberOfVariables();
    void printClauses();
};

# endif
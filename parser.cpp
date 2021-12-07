#include <iostream>
#include <fstream>
#include <string>
#include <vector>

std::string trim(const std::string s)
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

int stringToInt(const std::string number)
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
            for (int i = number.length() - 1; i >= 1; i--)
            {
                converted = (number[i] - 48) + 10*converted;
            }
            converted *= -1;
        }
        else 
        {
            for (int i = number.length() - 1; i >= 0; i--)
            {
                converted = (number[i] - 48) + 10*converted;
            }
        }
        return converted;
    }
}

int main(int argc, char **argv) 
{
   std::string line;
   std::ifstream dimacs (argv[1]);
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
                   // Problem line
                   std::string token = "";
                   for (int j = 0; j < line.length(); j++) 
                   {
                       if (line[j] == ' ')
                       {
                           std::cout << token << "\n";
                           token = "";
                       }
                       else 
                       {
                           token += line[j];
                       }
                   }
                   std::cout << token << "\n";
               }
               else 
               {
                   // Clauses
                   std::string number = "";
                   std::vector<int> clause;
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
                   for (auto x : clause)
                   {
                       std::cout << x << " ";
                   }
                   std::cout << "\n";
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
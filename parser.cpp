#include <iostream>
#include <fstream>
#include <string>

int main(int argc, char **argv) 
{
   std::string line;
   std::ifstream dimacs (argv[1]);
   if (dimacs.is_open()) 
   {
       while (getline(dimacs, line)) 
       {
           int i = 0;
           while (line[i] == ' ') 
           {
               // Skip whitespaces at the start
               i++;
           }
           if (i == line.length()) 
           {
               // Line consists of whitespaces only
           }
           else 
           {
               if (line[i] == 'c') 
               {
                   // Comment lines which can be ignored
               }
               else if (line[i] == 'p') 
               {
                   // Problem line
                   std::string token = "";
                   for (int j = i; j < line.length(); j++) 
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
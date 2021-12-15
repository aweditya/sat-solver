# SAT Solver
This repository contains an implementation of a SAT Solver in C++ using the _DPLL (Davis-Putnam-Logemann-Loveland) Algorithm_. The algorithm uses a backtracking approach to decide the satisfiability of propositional logic formulae in **Conjunctive Normal Form**.

## DIMACS format
The CNF problem is represented using the _DIMACS format_. A description of the same along with some examples can be found [here](https://people.sc.fsu.edu/~jburkardt/data/cnf/cnf.html).

## Files
* ```parser.cpp``` contains code for parsing _.cnf_ files and returning clauses for the problem instance
* ```dpll.cpp``` uses a basic backtracking algorithm
* ```dpll-improved.cpp``` also uses _Unit Propagation_ and _Pure Literal Elimination_ to speed-up backtracking 



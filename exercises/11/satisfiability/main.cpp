#include "satisfiability.h"

#include <iostream>

int main()
{  
    int cases;
    std::cin >> cases;

    for (int i{0}; i < cases; i++)
    {
	Satisfiability<40> sat;
    	int var_count, claus_count;
    	std::cin >> var_count;
    	std::cin >> claus_count;
	
    	std::vector<std::string> clauses(claus_count);

    	std::cin.get();
    	for (int c{0}; c < claus_count; c++)
    	{
    	    std::string str;
    	    std::getline(std::cin, str);
    	    clauses[c] = str;
    	}
	sat.add_clauses(clauses);
    	bool res = sat.check_satisfiability();
    	if (res)
    	    std::cout << "satisfiable" << std::endl;
    	else
    	    std::cout << "unsatisfiable" << std::endl;
    }
}

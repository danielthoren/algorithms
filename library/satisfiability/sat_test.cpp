#include <vector>
#include <string>
#include <iostream>

#include "satisfiability.h"

using namespace std;

bool is_satisfiable(std::vector<std::string> const& clauses, char negation = '~', char or_sign = 'v')
{
    Satisfiability sat(clauses, negation, or_sign);

    return sat.check_satisfiability();
}

int main()
{
    {
    	std::vector<std::string> data{
    	        "~x v y", 
    		"~y v z",
    		"x v ~z v y" };

    	if (!is_satisfiable(data))
    	{
    	    cout << "Error, expected satisfiable problem 1" << endl;
    	}
    }

    {
    	std::vector<std::string> data{"-xa1 p -xb1",
    				      "-xa1 p -xc1",
    				      "-xa1 p -xd1",
    				      "-xb1 p -xc1",
    				      "-xb1 p -xd1" ,
    				      "-xc1 p -xd1"};

    	if (!is_satisfiable(data, '-', 'p'))
    	{
    	    cout << "Error, expected satisfiable problem 2" << endl;
    	}
    }

    
    {
	std::vector<std::string> data{"~x v ~x",
				      "x v x"};

	if (is_satisfiable(data))
	{
	    cout << "Error, expected unsatisfiable problem 3" << endl;
	}
    }
}

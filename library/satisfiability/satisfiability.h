#ifndef SATISFIABILITY
#define SATISFIABILITY

#include <vector>
#include <bitset>
#include <string>
#include <map>

namespace dalg
{

    /**
     * Class with operations to check satisfiability of a number of
     * clauses. Uses brute force to find a solution thus verry slow.
     *
     * VAR_COUNT: The amount of bits in the bitset, 
     *            must be at least the number of variables * 2
     *
     *
     * vars  : The values of the variables on the following format:
     *         "x1, ~x1, x2, ~x2, ..." 
     * clause: The clause on the format "01001.." where each position corresponds to the 
     *         same position in variables. 
     *         If it is a 1 then that variable is in the clause, otherwise not
     *
     * Every permutation of the "vars" is then tested until either a
     * combination that satisfies all clauses is found or until all
     * combinations has been tested.
     */
    template<int SIZE = 40>
    class Satisfiability
    {
    public:
	Satisfiability(char negation = '~', char or_sign = 'v') :
	    vars{},
	    result{},
	    clauses{},
	    negation{negation},
	    or_sign{or_sign}
	
	    {
		init_vars();
	    }

	Satisfiability(std::vector<std::string> const& clauses, char negation = '~', char or_sign = 'v') :
	    vars{},
	    result{},
	    clauses{},
	    negation{negation},
	    or_sign{or_sign}
	
	    {
		init_vars();
		add_clauses(clauses);
	    }

	/**
	 * Adds the given clause, a clause must have the following format:
	 * "x1 v x2 v ~x3"
	 * 
	 * Where ~ indicates negation and v is the sign for and. The names
	 * of the variables can be anything
	 */
	void add_clause(std::string const& clause);

	/**
	 * Adds all clauses in the vector
	 */
	void add_clauses(std::vector<std::string> const& clauses);


	/**
	 * Calculates the satisfiability of the given clauses by testing
	 * every permutation of the variables.
	 *
	 * Time Complexity: O(2^n) n = number of variables
	 */
	bool check_satisfiability();

	std::bitset<SIZE> get_solution() const;
	std::string get_str_solution() const;


    private:

	/**
	 * Author: Daniel Thorén
	 *
	 * Checks if the clauses are satisfied given the value of the given variables.
	 *
	 * VAR_COUNT: The amount of bits in the bitset, 
	 *            must be at least the number of variables * 2
	 *
	 * vars  : The values of the variables on the following format:
	 *         "x1, ~x1, x2, ~x2, ..." 
	 * clause: The clause on the format "01001.." where each position corresponds to the 
	 *         same position in variables. 
	 *         If it is a 1 then that variable is in the clause, otherwise not
	 *
	 * return: True if clause is satisfied, otherwise false 
	 */
	bool all_satisfied(std::bitset<SIZE> const& vars);


	/**
	 * Author: Daniel Thorén
	 *
	 * Looks for a way to satisfy the given clauses, returns true when a
	 * solution has been found.
	 * 
	 * VAR_COUNT: The amount of bits in the bitset, 
	 *            must be at least the number of variables * 2
	 *
	 * Time complexity: O(2^n) n = var_count
	 *
	 * vars  : The values of the variables on the following format:
	 *         "x1, ~x1, x2, ~x2, ..." 
	 * clause: The clause on the format "01001.." where each position corresponds to the 
	 *         same position in variables. 
	 *         If it is a 1 then that variable is in the clause, otherwise not
	 *
	 * return: True if clause is satisfied, otherwise false. If true then
	 *         a solution is stored in result
	 */
	bool help_satisfiability(unsigned pos, std::bitset<SIZE>& vars);

	/**
	 * Initializes the variables so that all variables start at 0 and
	 * their respective negations start at 1
	 */
	void init_vars();
    
	std::bitset<SIZE> vars;
	std::bitset<SIZE> result;
	std::vector<std::bitset<SIZE>> clauses;

	//Mapps between variable strings and positions in vars
	std::map<std::string, int> var_map;

	char negation;
	char or_sign;
    };

#include "satisfiability.tcc"
}
#endif

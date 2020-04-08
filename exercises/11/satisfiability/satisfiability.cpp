#include <vector>
#include <bitset>
#include <map>
#include <sstream>
#include <string>

#include <iostream>

/**
 * Checks if the given clause is satisfied given the value of the given variables.
 *
 * VAR_COUNT: The amount of variables including negations
 *
 * vars  : The values of the variables on the following format:
 *         "x1, ~x1, x2, ~x2, ..." 
 * clause: The clause on the format "01001.." where each position corresponds to the 
 *         same position in variables. 
 *         If it is a 1 then that variable is in the clause, otherwise not
 *
 * return: True if clause is satisfied, otherwise false 
 */
template<int VAR_COUNT>
inline bool is_satisfied(std::bitset<VAR_COUNT>& vars, std::bitset<VAR_COUNT> const& clause)
{
    std::bitset<VAR_COUNT> tmp =  (vars & clause);
    return tmp.any();
}

template<int VAR_COUNT>
bool get_satisfiable(int pos, int var_count,
		     std::bitset<VAR_COUNT> vars,
		     std::vector<std::bitset<VAR_COUNT>> const& clauses)
{
    bool all_satisfied{true};
    for (std::bitset<VAR_COUNT> const& clause : clauses)
    {
	if (!is_satisfied<VAR_COUNT>(vars, clause))
	    all_satisfied = false;
    }

    if (all_satisfied)
	return true;
    
    // if (pos == VAR_COUNT)
    // 	return false;

    if (pos == var_count*2)
	return false;

    std::bitset<VAR_COUNT> var_perm{vars};
    var_perm.flip(pos);
    var_perm.set(pos+1, !var_perm[pos]);
    
    return get_satisfiable<VAR_COUNT>(pos + 2, var_count, vars, clauses) ||
	get_satisfiable<VAR_COUNT>(pos + 2, var_count, var_perm, clauses);
}

/**
 * This function uses bit operations to determine the satisfiability
 * of the given clauses. The clauses are structured in such a way that
 * a 1 on a certain position means that the corresponding variable is
 * in the clause. The variables are structured as follows:
 *
 * "x1, ~x1, x2, ~x2, .."
 *
 * Where ~ denotes the NOT operation
 *
 * VAR_COUNT: The amount of variables including negations
 *
 * var_count: the amount of variables
 * clauses  : All the clauses on the following format
 *            vector<"01001..."> where a 1 corresponds to that variable being 
 *            part of the clause. The structure of the variables can be seen above
 */
template<int VAR_COUNT>
bool is_satisfiable(std::vector<std::bitset<VAR_COUNT>> const& clauses, int var_count)
{
    std::bitset<VAR_COUNT> vars;

    for (int v{1}; v < var_count*2; v+=2)
    {
	vars[v] = 1;
    }    
    return get_satisfiable<VAR_COUNT>(0, var_count, vars, clauses);
}

template<int VAR_COUNT>
bool is_satisfiable(std::vector<std::string>& clauses, int var_count)
{
    std::vector<std::bitset<VAR_COUNT>> bit_clauses{};

    int var_nr{0};
    std::map<std::string, int> var_map;

    for (int pos{0}; pos < clauses.size(); pos++)
    {
	std::stringstream stream(clauses[pos]);
	std::string next{};
	bit_clauses.emplace_back();

	while (stream >> next)
	{
	    if (next != "v")
	    {
		bool neg{false};
		if (next[0] == '~')
		{
		    neg = true;
		    next.erase(next.begin());
		}
		    
		auto it = var_map.find(next);
		if (it == var_map.end())
		{
		    var_map.insert({next, var_nr});
		    var_nr += 2;
		    it = var_map.find(next);
		}
		if (neg)
		    bit_clauses[pos].set(it->second + 1, 1);
		else
		    bit_clauses[pos].set(it->second, 1);
	    }
	    next.clear();
	}
    }

    return is_satisfiable<VAR_COUNT>(bit_clauses, var_count);
}

int main()
{
    // std::vector<std::string> clauses{"x1 v x2", "~x1", "~x2 v x3"};

    // std::cout << is_satisfiable<40>(clauses, 3) << std::endl;
    
    // std::vector<std::string> clauses2{"x1 v x2 v x3", "x1 v ~x2", "x2 v ~x3", "x3 v ~x1", "~x1 v ~x2 v ~x3"};

    // std::cout << is_satisfiable<40>(clauses2, 3) << std::endl;
  
    int cases;
    std::cin >> cases;

    for (int i{0}; i < cases; i++)
    {
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
    	bool sat = is_satisfiable<40>(clauses, var_count);
    	if (sat)
    	    std::cout << "satisfiable" << std::endl;
    	else
    	    std::cout << "unsatisfiable" << std::endl;
    }
}



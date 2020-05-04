#include <sstream>

#ifndef SATISFIABILITY
#error 'satisfiability.tcc' is not supposed to be included directly. Include 'satisfiability.h' instead.
#endif

template<int SIZE>
bool dalg::Satisfiability<SIZE>::all_satisfied(std::bitset<SIZE> const& vars)
{
    bool all_satisfied{true};
    for (std::bitset<SIZE> const& clause : clauses)
    {
	if (! (vars & clause).any() )
	    all_satisfied = false;
    }
    return all_satisfied;
}


template<int SIZE>
bool dalg::Satisfiability<SIZE>::check_satisfiability()
{
    init_vars();
    return help_satisfiability(0, vars);
}


template<int SIZE>
bool dalg::Satisfiability<SIZE>::help_satisfiability(unsigned pos, std::bitset<SIZE>& vars)
{
    if (all_satisfied(vars))
    {
	this->result = vars;
	return true;
    }

    if (pos == var_map.size()*2)
	return false;

    std::bitset<SIZE> var_perm{vars};
    var_perm.flip(pos);
    var_perm.set(pos+1, !var_perm[pos]);
    
    return help_satisfiability(pos + 2, vars) ||
	help_satisfiability(pos + 2, var_perm);
}

template<int SIZE>
void dalg::Satisfiability<SIZE>::init_vars()
{
    for (unsigned v{1}; v < var_map.size()*2; v+=2)
    {
	vars[v] = 1;
    }
}

template<int SIZE>
std::bitset<SIZE> dalg::Satisfiability<SIZE>::get_solution() const
{
    return result;
}

template<int SIZE>
std::string dalg::Satisfiability<SIZE>::get_str_solution() const
{
    std::stringstream stream{};
    for (auto it = var_map.begin(); it != var_map.end(); it++)
    {
	if (result[it->second] == 1)
	{
	    stream << it->first << ": true " << std::endl;
	}
	else
	{
	    stream << it->first << ": false " << std::endl;
	}
    }
    return stream.str();
}

template<int SIZE>
void dalg::Satisfiability<SIZE>::add_clause(std::string const& clause)
{
    std::stringstream stream(clause);
    std::string next{};
    clauses.emplace_back();
    int pos = clauses.size() - 1;

    while (stream >> next)
    {
	if (next[0] != or_sign)
	{
	    bool neg{false};
	    if (next[0] == negation)
	    {
		neg = true;
		next.erase(next.begin());
	    }
		    
	    auto it = var_map.find(next);
	    if (it == var_map.end())
	    {
		var_map.insert({next, var_map.size() * 2});
		it = var_map.find(next);
	    }
	    if (neg)
		clauses[pos].set(it->second + 1, 1);
	    else
		clauses[pos].set(it->second, 1);
	}
	next.clear();
    }
}

template<int SIZE>
void dalg::Satisfiability<SIZE>::add_clauses(std::vector<std::string> const& clauses)
{
    for (unsigned pos{0}; pos < clauses.size(); pos++)
    {
	add_clause(clauses[pos]);
    }
}

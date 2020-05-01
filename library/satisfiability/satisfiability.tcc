#include <sstream>

#ifndef SATISFIABILITY
#error 'satisfiability.tcc' is not supposed to be included directly. Include 'satisfiability.h' instead.
#endif

template<int SIZE>
bool Satisfiability<SIZE>::all_satisfied(std::bitset<SIZE> const& vars)
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
bool Satisfiability<SIZE>::check_satisfiability()
{
    init_vars();
    return help_satisfiability(0, vars);
}


template<int SIZE>
bool Satisfiability<SIZE>::help_satisfiability(int pos, std::bitset<SIZE>& vars)
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
void Satisfiability<SIZE>::init_vars()
{
    for (int v{1}; v < var_map.size()*2; v+=2)
    {
	vars[v] = 1;
    }
}

template<int SIZE>
std::bitset<SIZE> Satisfiability<SIZE>::get_solution() const
{
    return result;
}

template<int SIZE>
std::string Satisfiability<SIZE>::get_str_solution() const
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
void Satisfiability<SIZE>::add_clause(std::string const& clause)
{
    std::stringstream stream(clause);
    std::string next{};
    clauses.emplace_back();
    int pos = clauses.size() - 1;

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
void Satisfiability<SIZE>::add_clauses(std::vector<std::string> const& clauses)
{
    for (int pos{0}; pos < clauses.size(); pos++)
    {
	add_clause(clauses[pos]);
    }
}

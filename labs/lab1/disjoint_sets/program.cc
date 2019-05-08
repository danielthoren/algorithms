#include <vector>
#include <iostream>
#include <numeric>

void print_sets(std::vector<int>& sets)
{
    for (int i = 0; i < sets.size(); i++)
	std::cout << "elem: " << i << " -> " << sets.at(i) << std::endl;
}

int compress_find(int elem, std::vector<int>& sets)
{
    std::vector<int> elems;
    while (sets.at(elem) != elem)
    {
	elems.push_back(elem);
	elem = sets.at(elem);
    }
    for (int e : elems)
	sets.at(e) = elem;
    return elem;
}

bool is_joined(int a, int b, std::vector<int>& sets)
{
    sets.at(a) = compress_find(a, sets);
    sets.at(b) = compress_find(b, sets);
    return sets.at(a) == sets.at(b);
}

void join(int a, int b, std::vector<int>& sets)
{   
    sets.at(compress_find(b, sets)) = compress_find(a, sets);
}

int main()
{
    int base_set_elems; //N
    int operations;     //Q

    std::ios_base::sync_with_stdio(false);

    std::cin >> base_set_elems >> operations;
    
    std::vector<int> sets(base_set_elems);
    std::iota(sets.begin(), sets.end(), 0);

    for (int i = 0; i < operations; i++)
    {
	char op;
	std::cin >> op;
	int a, b;
	std::cin >> b >> a;

	if(op == '?')
	{
	    if (is_joined(a, b, sets))
		std::cout << "yes" << std::endl;
	    else
		std::cout << "no" << std::endl;
	}
	else if (op == '=')
	{
	    join(a, b, sets);
	}

	//print_sets(sets);
    }
    return 0;
}

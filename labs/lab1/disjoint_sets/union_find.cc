#include <vector>
#include <iostream>
#include <numeric>


/**
 * This class keeps track of a number of elements partitioned into a
 * number of disjoint subsets. It provides the standard functions of a
 * union find algorithm
 */
class Union_find
{
public:
    Union_find(int size) : sets(size)
	{
	    std::iota(sets.begin(), sets.end(), 0);
	}

    /**
     * Prints all the sets
     */    
    void print_sets()
	{
	    for (int i = 0; i < sets.size(); i++)
		std::cout << "elem: " << i << " -> " << sets.at(i) << std::endl;
	}

    /**
     * Returns true if the elements belongs to the same set
     */
    bool is_joined(int a, int b)
	{
	    sets.at(a) = compress_find(a);
	    sets.at(b) = compress_find(b);
	    return sets.at(a) == sets.at(b);
	}

    /**
     * Joints the set that a belongs to with the set that b belongs to
     */
    void join(int a, int b)
	{   
	    sets.at(compress_find(b)) = compress_find(a);
	}

private:

    /**
     * return: The root element that elem belongs to
     */
    int compress_find(int elem)
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
    

    /**
     * The vector represents data in the following way:
     * parent = sets.at(elem)
     *
     * Each number between 0 and sets.size() represents an element and
     * the data at the position of each element represents its
     * parent. If an element has itself as a parent it is the root
     * element.
     */    
    std::vector<int> sets{};
};

int main()
{
    int base_set_elems; //N
    int operations;     //Q

    scanf(" %d", &base_set_elems);
    scanf(" %d", &operations);

    //STD::ios_base::sync_with_stdio(false);

    //std::cin >> base_set_elems >> operations;
    
    Union_find set(base_set_elems);

    for (int i = 0; i < operations; i++)
    {
	char op;
	scanf(" %c", &op);	
	
	//	std::cin >> op;
	int a, b;
	scanf(" %d", &a);
	scanf(" %d", &b);
	//std::cin >> b >> a;

	if(op == '?')
	{
	    if (set.is_joined(a, b))
		printf("yes\n");
	    else
		printf("no\n");
	}
	else if (op == '=')
	{
	    set.join(a, b);
	}

	//print_sets(sets);
    }
    return 0;
}


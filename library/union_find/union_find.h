#include <vector>
#include <iostream>
#include <numeric>

#ifndef UNION_FIND
#define UNION_FIND

/**
 * Author: Daniel Thorén
 *
 * This class keeps track of a number of elements partitioned into a
 * number of disjoint subsets. It provides the standard functions of a
 * union find algorithm.
 *
 * Template must be of integer type
 */
template <typename T>
class Union_find
{
public:
    Union_find(T size) : sets(size)
	{
	    std::iota(sets.begin(), sets.end(), 0);
	}

    /**
     * Prints all the sets
     */    
    void print_sets()
	{
	    for (T i = 0; i < sets.size(); i++)
		std::cout << "elem: " << i << " -> " << sets.at(i) << std::endl;
	}

    /**
     * Returns true if the elements belongs to the same set
     *
     * Complexity: O(log n)
     *
     * a: element 1
     * b: element 2
     */
    bool is_joined(T a, T b)
	{
	    sets.at(a) = compress_find(a);
	    sets.at(b) = compress_find(b);
	    return sets.at(a) == sets.at(b);
	}

    /**
     * Joints the set that a belongs to with the set that b belongs to
     *
     * Complexity: O(log n)
     *
     * a: element 1
     * b: element 2
     */
    void join(T a, T b)
	{   
	    sets.at(compress_find(b)) = compress_find(a);
	}

private:

    /**
     * Complexity: O(log n)
     *
     * elem: The element to find
     * return: The root element that elem belongs to
     */
    int compress_find(T elem)
	{
	    std::vector<T> elems;
	    while (sets.at(elem) != elem)
	    {
		elems.push_back(elem);
		elem = sets.at(elem);
	    }
	    for (T e : elems)
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
    std::vector<T> sets{};
};

#endif

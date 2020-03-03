#include <vector>
#include <iostream>

/* Author: Daniel Thorén
 *
 * Fenwick tree (Binary indexed tree) implementation.  Efficiently
 * update elements and calculate prefix sums. A prefix sum, also
 * called an accumulative sum is just the sum of all elements up until
 * a given index in the following way:
 * y0 = x0
 * y1 = x0 + x1
 * y2 = x0 + x1 + x2
 *...
 *
 * template T must be of integer type (int, long,
 * unsigned int etc)
 */
template <typename T>
class FenwickTree
{
public:

    /**
     * size: the size of the tree
     */
    FenwickTree(long unsigned int size) : tree(size + 1)
	{}

    /**
     * Constructs a tree from the given values
     *
     * StartValues: The starting values of the tree
     */
    FenwickTree(std::vector<T>& startValues) :
	tree(startValues.size() + 1)
	{
	    for (int i{0}; i < startValues.size(); i++)
	    {
		update(i, startValues[i]);
	    }
	}

    /**
     * Updates the value at index to val. This operation requires all
     * nodes in the tree dependant on the value of the indexed node to
     * be updated. 
     * If there is a j < i1 where i1 is the LSB of the current node n then
     * n is a decendant of n + 2^i1
     *
     * Time complexity: O(log n)
     * Memory complexity: O(n)
     * 
     * index: The index to update
     * val  : The value to update with
     */
    void update(T index, T val)
	{
	    index += 1;
	    while (index < tree.size())
	    {
		tree.at(index) += val;
		index += index & (-index);
	    }
	}

    /**
     * Returns the prefix sum up until the given index. This is done
     * by visiting each parent node of the index node and adding the
     * cached sums in them. The next parent to visit is calculated by
     * removing the right-most bit of the binary representation of the
     * current index.
     *
     * Time complexity: O(log n)
     * Memory complexity: O(n)
     *
     * index: The index where the cumulative sum stops
     */
    T sum(T index)
	{
	    T res = 0;
	    while (index > 0)
	    {
		res += tree.at(index);
		index -= index & (-index);
	    }
	    return res;
	}

    /**
     * Returns the sum between the given indexes
     *
     * from: The start index of the range
     * to  : The end index of the range
     */
    T ranged_sum(T from, T to)
	{
	    T f = sum(from);
	    T t = sum(to);

	    return t - f;
	}

private:
    std::vector<T> tree;
};

int main()
{
    long arr_length;
    long num_ops;

    scanf(" %ld", &arr_length);
    scanf(" %ld", &num_ops);
    
    FenwickTree<long> tree(arr_length);
    long index, num, res;
    for (int i = 0; i < num_ops; i++)
    {
	char in;
	scanf(" %c", &in);

	if (in == '+')
	{
	    scanf(" %ld", &index);
	    scanf(" %ld", &num);
	    
	    tree.update(index, num);
	}
	else
	{
	    scanf(" %ld", &index);
	
	    res = tree.sum(index);

	    printf("%ld\n", res);
	}
    }
	  
    
    return 0;
}

#include <vector>
#include <iostream>

/*
 * Fenwick tree (Binary indexed tree) implementation
 * template T must be of integer type
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
     * Updates the value at index to val
     *
     * Complexity: O(log n)
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
     * Returns the value at the provided index
     *
     * Complexity: O(log n)
     *
     * index: The index to fetch data from
     */
    T query(T index)
	{
	    T res = 0;
	    while (index > 0)
	    {
		res += tree.at(index);
		index -= index & (-index);
	    }
	    return res;
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
	
	    res = tree.query(index);

	    printf("%ld\n", res);
	}
    }
	  
    
    return 0;
}

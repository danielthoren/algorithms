#include <vector>
#include <iostream>

/*
 * Fenwick tree implementation, template type must be of integer type
 */
template <typename T>
class FenwickTree
{
public:

    FenwickTree(long unsigned int size) : tree(size + 1)
	{}	
    
    void update(T index, T val)
	{
	    index += 1;
	    while (index < tree.size())
	    {
		tree.at(index) += val;
		index += index & (-index);
	    }
	}

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

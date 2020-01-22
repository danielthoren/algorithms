#include <vector>
#include <iostream>


template <typename T>
void update(T index, T val, std::vector<T>& tree)
{
    index += 1;
    while (index < tree.size())
    {
	tree.at(index) += val;
	index += index & (-index);
    }
}

template <typename T>
T query(T index, std::vector<T>& tree)
{
    T res = 0;
    while (index > 0)
    {
	res += tree.at(index);
	index -= index & (-index);
    }
    return res;
}

int main()
{
    long arr_length;
    long num_ops;

    scanf(" %ld", &arr_length);
    scanf(" %ld", &num_ops);
    
    std::vector<long> tree(arr_length + 1);
    long index, num, res;
    for (int i = 0; i < num_ops; i++)
    {
	char in;
	scanf(" %c", &in);

	if (in == '+')
	{
	    scanf(" %ld", &index);
	    scanf(" %ld", &num);
	    
	    update<long>(index, num, tree);
	}
	else
	{
	    scanf(" %ld", &index);
	
	    res = query<long>(index, tree);

	    printf("%ld\n", res);
	}
    }
	  
    
    return 0;
}

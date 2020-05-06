
#include "fenwick_tree.h"

int main()
{
    long arr_length;
    long num_ops;

    scanf(" %ld", &arr_length);
    scanf(" %ld", &num_ops);
    
    dalg::FenwickTree<long> tree(arr_length);
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

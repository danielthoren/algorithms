
#ifndef FENWICK_TREE
#error 'fenwick_tree.tcc' is not supposed to be included directly. Include 'fenwick_tree.h' instead.
#endif

template <typename T>
dalg::FenwickTree<T>::FenwickTree(std::vector<T>& startValues) :
    tree(startValues.size() + 1)
{
    for (int i{0}; i < startValues.size(); i++)
    {
	update(i, startValues[i]);
    }
}

template <typename T>
void dalg::FenwickTree<T>::update(long unsigned index, T val)
{
    index += 1;
    while (index < tree.size())
    {
	tree.at(index) += val;
	index += index & (-index);
    }
}


template <typename T>
T dalg::FenwickTree<T>::sum(long unsigned index)
{
    T res = 0;
    while (index > 0)
    {
	res += tree.at(index);
	index -= index & (-index);
    }
    return res;
}

template <typename T>
T dalg::FenwickTree<T>::ranged_sum(long unsigned from, long unsigned to)
{
    T f = sum(from);
    T t = sum(to);

    return t - f;
}


template <typename T>
FenwickTree<T>::FenwickTree(std::vector<T>& startValues) :
    tree(startValues.size() + 1)
{
    for (int i{0}; i < startValues.size(); i++)
    {
	update(i, startValues[i]);
    }
}

template <typename T>
void FenwickTree<T>::update(T index, T val)
{
    index += 1;
    while (index < tree.size())
    {
	tree.at(index) += val;
	index += index & (-index);
    }
}


template <typename T>
T FenwickTree<T>::sum(T index)
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
T FenwickTree<T>::ranged_sum(T from, T to)
{
    T f = sum(from);
    T t = sum(to);

    return t - f;
}

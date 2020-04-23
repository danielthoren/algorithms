template <typename T>
void help_subset_sum(std::vector<T> const& numbers,
		     T target,
		     std::vector<std::vector<T>>& result,
		     std::vector<T> subset,
		     T curr_index,
		     T curr_sum,
		     T min_elems,
		     T max_elems)
{
    if (curr_sum > target || subset.size() > max_elems)
    {
	return;
    }

    subset.push_back(numbers[curr_index]);
    
    if (curr_sum == target && subset.size() >= min_elems)
    {
	result.push_back(subset);
	return;
    }

    for (T i{curr_index + 1}; i < numbers.size(); i++)
    {
	help_subset_sum<T>(numbers, target, result, subset, i, curr_sum + numbers[i], min_elems, max_elems);	
    }
}

template <typename T>
std::vector<std::vector<T>> subset_sum(std::vector<T>& numbers,
				       T target,
				       T min_elems,
				       T max_elems)
{
    std::vector<T> subset{};
    std::vector<std::vector<T>> result{};

    std::sort(numbers.begin(), numbers.end());

    for (int i{0}; i < numbers.size(); i++)
    {
	help_subset_sum<T>(numbers, target, result, subset, i, numbers[i], min_elems, max_elems);
    }

    return result;
}

template <typename T>
std::string print_subsets(std::vector<std::vector<T>> const& subset)
{
    std::stringstream stream{};
    
    for (std::vector<T> const& set : subset)
    {
	stream << "{";
	T sum{0};
	for (T i{0}; i < set.size() - 1; i++)
	{
	    sum += set[i];
	    stream << set[i] << ", ";
	}
	sum += set[set.size() - 1];
	stream << set[set.size() - 1] << "} = " << sum << std::endl;
    }
    return stream.str();
}

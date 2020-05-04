#ifndef SUBSET_SUM
#define SUBSET_SUM

#include <vector>
#include <limits>

namespace dalg
{

    /**
     * Solves the subset sum problem. Given a vector of numbers, what
     * possible subsets of theese numbers gives the target value when
     * summed together. This problem is NP hard thus this is a brute force
     * solution.
     *
     * Time complexity: Exponential
     *
     * numbers  : The numbers to pick from
     * target   : The target sum
     * min_elems: Lower limit on how many elements from "numbers" must be picked
     * max_elems: Uppger limit on how many elements from "numbers" must be picked
     * 
     * return: A vector containing alsubsets meeting the requirements
     */
    template <typename T>
    std::vector<std::vector<T>> subset_sum(std::vector<T>& numbers,
					   T target,
					   T min_elems = std::numeric_limits<T>::min(),
					   T max_elems = std::numeric_limits<T>::max());

    /**
     * Prints the result from the subset_sum function
     */
    template <typename T>
    std::string print_subsets(std::vector<std::vector<T>> const& subset);

#include "subset_sum.tcc"
}
#endif

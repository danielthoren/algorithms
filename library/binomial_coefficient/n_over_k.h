#include <vector>

#ifndef N_OVER_K
#define N_OVER_K

/**
 * Calculates the binomial coefficient n over k using the pascal
 * triangle. Dynamic programming approach that trades memory space for
 * time. Is faster if using the same triag multiple times.
 *
 * Time complexity  : O(n^2) (first time then reusing previous results)
 * Memory complexity: O(n^2)
 *
 * n    : The n in n over k
 * k    : The k in n over k
 * triag: The saved pascal triangle, should be used multiple times
 */
template <typename T>
T n_over_k(T n, T k, std::vector<std::vector<T>>& triag);


/**
 * Calculates the binomial coefficient n over k with brute force. Uses
 * less memory and just as slow as the above variant the first time it
 * is run. This solution does not reuse already calculated values thus
 * slower when calculating multiple values.
 *
 * Time complexity  : O(n^2)
 * Memory complexity: O(1)
 *
 * n    : The n in n over k
 * k    : The k in n over k
 */	   
template <typename T>
T n_over_k(T n, T k);

#include "n_over_k.tcc"

#endif

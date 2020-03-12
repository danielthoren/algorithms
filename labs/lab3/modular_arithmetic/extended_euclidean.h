#ifndef EXTENDED_EUCLIDEAN
#define EXTENDED_EUCLIDEAN

#include <tuple>

/**
 * Author: Daniel Thorén
 *
 * Performs true mod in the mathmatical sense. Normal % operator does
 * not work as expected when using negative numbers. This method
 * always returns posetive results
 *
 * num: The number to mod
 * mod: The base
 *
 * return: The result
 */
template<typename T>
T true_mod(T num, T mod);

/**
 * Author: Daniel Thorén
 *
 * The extened euclidean algorithm calculates GCD(a, b) and the 
 * Bezout coefficients S, T which ar defined as follows:
 * a*S + b*T = GCD(a, b) = d
 *
 * Template type T must be of integer type (int, long...)
 *
 * Time complexity: O(log n) where n is max(a, b)
 *
 * a : One of the numbers to calculate gcd
 * b : One of the numbers to calculate gcd
 *
 * return: tuple containing (r, s, t) 
 *         where r = GCD(a, b) and s,t are Becout coefficients
 */
template<typename T>
std::tuple<T, T, T> extended_euclidean(T a, T b);

/**
 * Author: Daniel Thorén
 *
 * Returns the modular multiplicative inverse of num.
 * Template must be of integer type (int, long...)
 *
 * Time complexity: O( (log n)^n )
 *
 * num: The number to get the multiplicative inverse of
 * mod: The modulus number
 *
 * return: The multiplicative inverse
 */
template<typename T>
T get_modular_inverse(T num, T mod);



/*************************************************************/
/* Should be in tcc file, temporarily here for kattis        */
/*************************************************************/


/**********************/
/* Member functions   */
/**********************/

#include <algorithm>
#include <vector>
#include <limits.h>
#include <functional>

template<typename T>
T true_mod(T num, T mod)
{
    T res = num % mod;
    if (res < 0)
	res += mod;
    return res;
}

template<typename T>
std::tuple<T, T, T> extended_euclidean(T a, T b)
{
    // Remainders, last remainder rk is the gcd
    T r{b};
    T r_prev{a};
    
    // Bezout coefficient s
    T s{0};
    T s_prev{1};

    // Bezout coefficient t
    T t{1};
    T t_prev{0};

    // Quotient
    T q{0};

    while (r != 0)
    {
	q = r_prev / r;
	
	T curr_r{r};
	r = r_prev - q*r;
	r_prev = curr_r;

	T curr_s{s};
	s = s_prev - q*s;
	s_prev = curr_s;

	T curr_t{t};
	t = t_prev - q*t;
	t_prev = curr_t;
    }
   
    return std::tuple<T, T, T>(r_prev, s_prev, t_prev);
}

template<typename T>
T get_modular_inverse(T num, T mod)
{
    std::tuple<int, int, int> res = extended_euclidean(num, mod);
    
    if (std::get<0>(res) != 1)
    {
	return -1;
    }
    else if (std::get<1>(res) < 0)
    {
	return std::get<1>(res) + mod;
    }
    return std::get<1>(res);
}


#endif

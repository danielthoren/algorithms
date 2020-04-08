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

#include "extended_euclidean.tcc"

#endif

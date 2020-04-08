#include <vector>
#include <string>

#ifndef PRIEME_SIEVE
#define PRIEME_SIEVE

/**
 * Author: Daniel Thorén
 *
 * Calculates which of all numbers between 2 and upper
 * that are prime numbers. This is done using the "sieve of
 * eratoshthenes" algorithm. The algorithm assumes that 1 is not a
 * prime number.
 *
 * Template must be of integer type (int, long, ...)
 *  
 * n = upper
 * Time complexity: O( n * log( log(n) ) )
 * Memory complexity: O(n)
 *
 * upper      : The number to find the sieve to
 * prime_count: This reference is set to the total number of primes found
 * return     : A vector<bool> where the value at each position determines 
 *              if that number is prime or not
 * 
 */
template<typename T>
std::vector<bool> prime_sieve(T upper, T& prime_count);


/**
 * Author: Daniel Thorén
 *
 * This function accepts a sieve and returns a vector containing all
 * primes thus separating the actual prime numbers from the rest.
 *
 * Time complexity: O(n)
 *
 * sieve : A prime sieve from the function prime_sieve(...)
 * return: A vector containing all primes
 */
template<typename T>
std::vector<T> get_primes(std::vector<bool>& sieve);


/**
 * Prints all elements in the given vector
 */
template<typename T>
std::string print_primes(std::vector<T> primes);

#include "prime_sieve.tcc"

#endif

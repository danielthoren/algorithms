#include <vector>
#include <string>

#ifndef PRIEME_SIEVE
#define PRIEME_SIEVE

template <typename T>
class Prime_sieve
{
public:

    Prime_sieve(T upper) : sieve{}, primes{}, prime_count{0}, upper{upper}
	{
	    prime_sieve();
	}

    /**
     * Returns the calculated prime sieve which is on the following format:
     * vector< true, true, false, ....>
     * If index is a prime then true, else false
     *
     * return: Sieve
     */
    std::vector<bool>& get_sieve();

    
    /**
     * Returns the calculated primes. Calls recalculate if the primes
     * vector is empty
     *
     * Time complexity: First time O(n)
     *
     * return: vector of the primes
     */
    std::vector<T>& get_primes();

    /**
     * Returns the amount of primes found. This is counted when
     * creating the sieve and can be retrieved in constant time after
     * the sieve has been calculated.
     *
     * Time complexity: O(1)
     */
    T get_prime_count();

    /**
     * Uses the primes to get the prime factors of num.
     *
     * Time complexity: O(n)
     *
     * num   : The number to calculate prime factors from
     * return: The prime factors of num
     */
    std::vector<T> get_prime_factors(T num);

   /**
    * Creates string of all primes
    *
    * return: String with all prime numbers
    */
    std::string print_primes();

private:

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
    void prime_sieve();

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
    void calc_primes();
    
    std::vector<bool> sieve;
    std::vector<T> primes;
    T prime_count;
    T upper;
};

#include "prime_sieve.tcc"

#endif

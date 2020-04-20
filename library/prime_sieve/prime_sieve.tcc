#include <functional>
#include <vector>
#include <algorithm>
#include <tuple>
#include <sstream>

#include <iostream>

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
std::vector<bool> prime_sieve(T upper, T& prime_count)
{
    std::vector<bool> nums(upper + 1);

    for (T i{2}; i < upper + 1; i++)
    {
	nums[i] = true;
    }

    //Not counting 0 and 1 as primes
	nums[0] = false;
	nums[1] = false;

	T p{2};
	T prime_counter{upper - 1};

	while (p < upper)
	{
	    T curr = p*p;

	    //Mark all multiples of p as not being prime
	    while (curr <= upper)
	    {
		if (nums[curr] == 1)
		    prime_counter--;
	    
		nums[curr] = 0;
		curr += p;
	    }

	    //Find the next prime number
	    do
	    {
		++p;
	    }
	    while (nums[p] == false && p < upper);
	}

	prime_count = prime_counter;
	return nums;
}

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
std::vector<T> get_primes(std::vector<bool>& sieve)
{
    std::vector<T> primes{};
    for (T i{2}; i <= sieve.size(); i++)
    {
	if (sieve[i] == true)
	{
	    primes.push_back(i);
	}
    }
    return primes; 
}


/**
 * Prints all elements in the given vector
 */
template<typename T>
std::string print_primes(std::vector<T> primes)
{
    std::stringstream stream;
    for (int i{0}; i < primes.size(); i++)
    {
	stream << primes[i] << ", ";
    }

    stream << std::endl;

    return stream.str();
}



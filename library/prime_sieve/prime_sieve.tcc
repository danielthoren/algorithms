#include <functional>
#include <vector>
#include <algorithm>
#include <tuple>
#include <sstream>
#include <cmath>

#ifndef PRIEME_SIEVE
#error 'prime_sieve.tcc' is not supposed to be included directly. Include 'prime_sieve.h' instead.
#endif

template<typename T>
std::vector<bool>& Prime_sieve<T>::get_sieve()
{
    return sieve;
}

template<typename T>
std::vector<T>& Prime_sieve<T>::get_primes()
{
    if (primes.size() == 0)
    {
	calc_primes();
    }
    return primes;
}

template<typename T>
T Prime_sieve<T>::get_prime_count()
{
    return prime_count;
}

template<typename T>
std::vector<T> Prime_sieve<T>::get_prime_factors(T num)
{
    if (num > upper * upper)
    {
	return {};
    }

    if (primes.size() == 0)
    {
	calc_primes();
    }

    std::vector<T> factors{};

    for (T prime : primes)
    {
	while (num % prime == 0)
	{
	    factors.push_back(prime);

	    num /= prime;
	}
    }

    if (num != 1)
    {
	factors.push_back(num);
    }

    return factors;
}

template<typename T>
std::vector<T> Prime_sieve<T>::get_unique_prime_factors(T num)
{
    std::vector<T> primes{ get_prime_factors(num) };

    std::vector<T> unique_primes{};

    T prev{ std::numeric_limits<T>::max() };
    for (T prime : primes)
    {
	if (prime != prev)
	{
	    unique_primes.push_back(prime);
	}
	prev = prime;
    }

    return unique_primes;
}

/**
 * Prints all elements in the given vector
 */
template<typename T>
std::string Prime_sieve<T>::print_primes()
{
    if (primes.size() == 0)
    {
	calc_primes();
    }
    std::stringstream stream;
    for (int i{0}; i < primes.size(); i++)
    {
	stream << primes[i] << ", ";
    }

    stream << std::endl;

    return stream.str();
}

template<typename T>
void Prime_sieve<T>::prime_sieve()
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

	while (p < std::sqrt(upper) )
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
	sieve = nums;
}

template<typename T>
void Prime_sieve<T>::calc_primes()
{
    for (unsigned i{2}; i <= sieve.size(); i++)
    {
	if (sieve[i] == true)
	{
	    primes.push_back(i);
	}
    }    
}



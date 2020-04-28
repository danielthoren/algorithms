#include <functional>
#include <vector>
#include <algorithm>
#include <tuple>
#include <sstream>
#include <cmath>

#include <iostream>

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
    if (num > upper)
    {
	return {};
    }

    if (primes.size() == 0)
    {
	calc_primes();
    }

    std::vector<T> factors{};
    long upper{ static_cast<long>(std::sqrt(num)) };

    for (int i{0}; i <= num && i < primes.size(); i++)
    {
	if (num % primes[i] == 0)
	{
	    factors.push_back(primes[i]);
	}
    }

    return factors;
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
	sieve = nums;
}

template<typename T>
void Prime_sieve<T>::calc_primes()
{
    for (T i{2}; i <= sieve.size(); i++)
    {
	if (sieve[i] == true)
	{
	    primes.push_back(i);
	}
    }    
}



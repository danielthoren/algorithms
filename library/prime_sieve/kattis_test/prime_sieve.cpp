#include <iostream>

#include "prime_sieve.h"

int main()
{
    long n, q;

    scanf(" %ld", &n);
    scanf(" %ld", &q);

    Prime_sieve<long> sieve(n);

    printf("%ld\n", sieve.get_prime_count());

    std::vector<bool>& primes = sieve.get_sieve();

    for (int i{0}; i < q; i++)
    {
	long x;
	scanf(" %ld", &x);

	if (x == 0 || x == 1)
	    printf("%d\n", (int) 0);
	else
	    printf("%d\n", (int) primes[x]);
    }
    return 0;
}

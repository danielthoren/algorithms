#include <iostream>

#include "prime_sieve.h"

int main()
{
    long n, q;

    scanf(" %ld", &n);
    scanf(" %ld", &q);

    long prime_count;

    std::vector<bool> primes = prime_sieve(n, prime_count);
    printf("%ld\n", prime_count);

    for (int i{0}; i < q; i++)
    {
	long x;
	scanf(" %ld", &x);

	printf("%d\n", (int) primes[x]);
    }
    return 0;
}

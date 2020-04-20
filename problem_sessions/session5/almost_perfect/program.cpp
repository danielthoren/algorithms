#include "prime_sieve.h"
#include <vector>

using namespace std;

long divisors(long num)
{
    long count;
    vector<bool> sieve = prime_sieve(num, count);
    vector<long> primes = get_primes<long>(sieve);

    vector<long> divisors{};

    for (int i{primes.size() - 1}; i >= 0; i--)
    {
	if (num % primes[i] == 0)
	{
	    int tmp{0};
	    while(num % primes[i] == 0)
	    {
		num = num / primes[i];
	    }
	}
    }
    return sum(
}

int main()
{
    while (true)
    {
	long n{0};
	scanf(" %ld", &n);
	if (n == 0)
	    break;       

	long res = divisors(n);
	printf("%ld\n", res);
    }
}


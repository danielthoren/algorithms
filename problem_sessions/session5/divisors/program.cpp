#include "prime_sieve.h"
#include <vector>

using namespace std;

long divisors(__int128 num)
{
    __int128 count;
    vector<bool> sieve = prime_sieve<__int128>(num, count);
    vector<__int128> primes = get_primes<__int128>(sieve);

    long divisors{1};
    for (int i{primes.size() - 1}; i >= 0; i--)
    {
	if (num % primes[i] == 0)
	{
	    int tmp{0};
	    while(num % primes[i] == 0)
	    {
		num = num / primes[i];
		++tmp;
	    }
	    divisors *= (tmp + 1);
	}
    }
    return divisors;
}

__int128 n_over_k(long n, long k, vector<vector<__int128>>& triag)
{
    if (triag.size() > n)
	return triag[n][k];
    
    long i, j; 
  
    for (i = triag.size(); i <= n; i++) 
    {
	triag.push_back( vector<__int128>() );
	
        for (j = 0; j <= i; j++) 
        { 
            if (j == 0 || j == i)
	    {
                triag[i].push_back(1);
	    }
            else
	    {
                triag[i].push_back( triag[i - 1][j - 1] + 
				    triag[i - 1][j] );
	    }
        } 
    } 
  
    return triag[n][k]; 
}

int main()
{
    vector<vector<__int128>> triag{};
    while (true)
    {
	long n{0};
	long k{0};
	scanf(" %ld", &n);
	if (n == 0)
	    break;
	
	scanf(" %ld", &k);
    
	__int128 num = n_over_k(n, k, triag);

	long res = divisors(num);
	printf("%ld\n", res);
    }
}

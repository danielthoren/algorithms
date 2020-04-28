
#include "prime_sieve.h"
#include <iostream>

using namespace std;

void print_vec(std::vector<long>& vec)
{
    for (long l : vec)
	cout << l << ", ";
    cout << endl;
}

int main()
{
    {
    	long num{100};
    	Prime_sieve<long> sieve(num);

    	std::vector<long> factors{ sieve.get_prime_factors(num) };

    	std::vector<long> correct{2, 5};

    	if (correct != factors)
    	{
    	    cout << "failed test with input: " << num << " Got:" << endl;
    	    print_vec(factors);
    	    cout << "expected: " << endl;
    	    print_vec(correct);
    	}
    }
    {
    	long num{1005005};
    	Prime_sieve<long> sieve(num);

    	std::vector<long> factors{ sieve.get_prime_factors(num) };

    	std::vector<long> correct{5, 19, 71, 149};

    	if (correct != factors)
    	{
    	    cout << "failed test with input: " << num << " Got:" << endl;
    	    print_vec(factors);
    	    cout << "expected: " << endl;
    	    print_vec(correct);
    	}
    }
    {
	long num{1234567};
	Prime_sieve<long> sieve(num);

	std::vector<long> factors{ sieve.get_prime_factors(num) };

	std::vector<long> correct{127, 9721};

	if (correct != factors)
	{
	    cout << "failed test with input: " << num << " Got:" << endl;
	    print_vec(factors);
	    cout << "expected: " << endl;
	    print_vec(correct);
	}
    }
	
}

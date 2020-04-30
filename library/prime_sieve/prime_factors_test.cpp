
#include "prime_sieve.h"
#include <iostream>

using namespace std;

void print_vec(std::vector<long> const& vec)
{
    for (long l : vec)
	cout << l << ", ";
    cout << endl;
}

void test(long num, vector<long> const& correct)
{
    Prime_sieve<long> sieve(num);

    std::vector<long> factors{ sieve.get_prime_factors(num) };

    if (correct != factors)
    {
	cout << "failed test with input: " << num << " Got:" << endl;
	print_vec(factors);
	cout << "expected: " << endl;
	print_vec(correct);
    }
}

int main()
{
    {
    	long num{100};
    	std::vector<long> correct{2, 2, 5, 5};

	test(num, correct);
    }
    {
	long num{147};
	std::vector<long> correct{3, 7, 7};

	test(num, correct);
    }
    {
	long num{17};
	std::vector<long> correct{17};

	test(num, correct);	
    }
    {
	long num{90};
	std::vector<long> correct{2,3,3,5};

	test(num, correct);
    }
    {
	long num{48};
	std::vector<long> correct{2,2,2,2,3};

	test(num, correct);
    }    
    {
    	long num{1005005};
    	std::vector<long> correct{5, 19, 71, 149};

	test(num, correct);
    }
    {
	long num{1234567};
	std::vector<long> correct{127, 9721};

	test(num, correct);
    }
    {
	long num{250};
	std::vector<long> correct{2, 5, 5, 5};

	test(num, correct);
    }
}

#include <string>
#include <vector>

using namespace std;

bool is_prime(long num)
{
    if (num <= 1)
	return false;
    else if (num == 3)
	return true;

    if (num % 2 == 0 || num % 3 == 0)
	return false;

    for (int i{5}; i * i <= num; i += 6)
    {
	if (num % i == 0 || num % (i + 2) == 0)
	{
	    return false;
	}
    }

    return true;
}

bool is_happy(long prime)
{        
    long res{prime};
    do
    {
	string nums{to_string(res)};
	res = 0;
	for (char c : nums)
	{
	    long num = (long) c - 48;
	    res += num * num;
	}

    } while (res != 1 && res != 4);

    return res == 1;
}

int main()
{
    long p;
    scanf(" %ld", &p);

    for (int i{0}; i < p; i++)
    {
	long num, prime;
	scanf(" %ld", &num);
        scanf(" %ld", &prime);

	if (is_prime(prime) && is_happy(prime))
	{
	    printf("%ld %ld YES\n", num, prime);
	}
	else
	{
	    printf("%ld %ld NO\n", num, prime);
	}
    }
    
}

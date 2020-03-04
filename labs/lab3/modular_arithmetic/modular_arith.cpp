#include <algorithm>
#include <vector>
#include <limits.h>
#include <functional>
#include <tuple>

#include <iostream>

/**
 * Performs true mod in the mathmatical sense. Normal % operator does
 * not work as expected when using negative numbers. This method
 * always returns posetive results
 *
 * num: The number to mod
 * mod: The base
 *
 * return: The result
 */
template<typename T>
T true_mod(T num, T mod)
{
    T res = num % mod;
    if (res < 0)
	res += mod;
    return res;
}

/**
 * The extened euclidean algorithm calculates GCD(a, b) and the 
 * Bezout coefficients S, T which ar defined as follows:
 * a*S + b*T = GCD(a, b) = d
 *
 * Template type T must be of integer type (int, long...)
 *
 * Time complexity: O(log n) where n is max(a, b)
 *
 * a : One of the numbers to calculate gcd
 * b : One of the numbers to calculate gcd
 *
 * return: tuple containing (r, s, t) 
 *         where r = GCD(a, b) and s,t are Becout coefficients
 */
template<typename T>
std::tuple<T, T, T> extended_euclidean(T a, T b)
{
    // Remainders, last remainder rk is the gcd
    T r{b};
    T r_prev{a};
    
    // Bezout coefficient s
    T s{0};
    T s_prev{1};

    // Bezout coefficient t
    T t{1};
    T t_prev{0};

    // Quotient
    T q{0};

    while (r != 0)
    {
	q = r_prev / r;
	
	T curr_r{r};
	r = r_prev - q*r;
	r_prev = curr_r;

	T curr_s{s};
	s = s_prev - q*s;
	s_prev = curr_s;

	T curr_t{t};
	t = t_prev - q*t;
	t_prev = curr_t;
    }
   
    return std::tuple<T, T, T>(r_prev, s_prev, t_prev);
}


/**
 * Returns the modular multiplicative inverse of num.
 * Template must be of integer type (int, long...)
 *
 * Time complexity: O( (log n)^n )
 *
 * num: The number to get the multiplicative inverse of
 * mod: The modulus number
 *
 * return: The multiplicative inverse
 */
template<typename T>
T get_modular_inverse(T num, T mod)
{
    std::tuple<int, int, int> res = extended_euclidean(num, mod);
    
    if (std::get<0>(res) != 1)
    {
	return -1;
    }
    else if (std::get<1>(res) < 0)
    {
	return std::get<1>(res) + mod;
    }
    return std::get<1>(res);
}

int main()
{
    int mod;
    long long ops;

    while (true)
    {
	scanf(" %d", &mod);
	scanf(" %lld", &ops);

	if (mod == 0 && ops == 0)
	    return 0;

	for (int i{0}; i < ops; i++)
	{
	    int x, y;
	    char op;
	
	    scanf(" %d", &x);
	    scanf(" %c", &op);
	    scanf(" %d", &y);

	    if (op == '/')
	    {
		int res = get_modular_inverse(y, mod);
		if (res == -1)
		{
		    printf("%d\n", res);
		}
		else
		{
		    printf("%d\n", true_mod<int>(x*res, mod));
		}
	    }
	    else if (op == '+')
	    {
		printf("%d\n", true_mod<int>(x+y, mod));
	    }
	    else if (op == '-')
	    {
		printf("%d\n", true_mod<int>(x-y, mod));
	    }
	    else if (op == '*')
	    {
		printf("%d\n", true_mod<int>(x*y, mod));
	    }
	}
    }
}


#include <algorithm>
#include <vector>
#include <limits.h>
#include <functional>

template<typename T>
T true_mod(T num, T mod)
{
    T res = num % mod;
    if (res < 0)
	res += mod;
    return res;
}

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

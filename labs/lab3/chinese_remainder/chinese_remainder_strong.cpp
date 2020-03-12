

#include "extended_euclidean.h"

#include <tuple>

/**
 * Merges two congruence equations using the strong chinese remainder
 * theorem, thus it is assumed that m1, m2 are not coprime. With other
 * words, it is assumed that GCD(m1, m2) != 1
 *
 * Both equations a1, m1, a2, m2 are on the form (= is congruence): 
 * x = 1a (mod 1m) (*1)
 *
 * If the following is true then there exists a solustion, otherwise not
 * gcd(m1, m2) = g
 * a1 = a2 mod g (where = is congruence) =>
 * a1 mod g == a2 mod g
 * If there is not solution then the function returns a tuple with only 0 in it
 * tuple<T, T>(0, 0)
 *
 * If a solution exists we know from Bezouts identity that there
 * is a solution to the following equation:
 * m1*S + m2*T = g <=>
 * (m1*S)/g + (m2*T)/g = 1 (*2)
 *
 * When Bezeouts coefficients (S, T) has been found the following
 * expression can be used to get the x in equation (*1):
 * x = (a1 * m2 * T) / g + (a2 * m1 * S) (*3)
 *
 * The smallest solution to the problem can be found by modding x from (*3)
 * with lcm(m1, m2):
 * lcm(m1, m2) = (m1 * m2) / gcd(m1, m2) = l
 * x = x mod l
 *
 * Time complexity: O(log n) (time complexity of extended_euclidean)
 *
 */
template<typename T>
std::tuple<T, T> merge_crt(T a1, T m1, T a2, T m2)
{

    //Calculating GCD(m1, m2) to check if there is a solution
    std::tuple<T, T, T> gcd_euclid = extended_euclidean(m1, m2);
    T g = std::get<0>(gcd_euclid);

    //If the following condition is not met then there is no solution:
    //gcd(m1, m2) = g
    //a1 = a2 mod g (where = is congruence)
    if (true_mod(a2, g) != true_mod(a1, g))
    {
	return std::make_tuple(0, 0);
    }
    
    //Extended euclidean gives <GCD(m1/g, m2/g), S, T
    //We know that there is a solution to the following equation:
    //m1*S + m2*T = g <=>
    //m1*S/g + m2*T/g = 1
    std::tuple<T, T, T> euclid = extended_euclidean(m1/g, m2/g);
    T s = std::get<1>(euclid);
    T t = std::get<2>(euclid);

    T x =
	a1 * (m2 / g) * t +
	a2 * (m1 / g) * s;

    //Find the smallest possible solution by modding x with lcm(m1, m2)
    T lcm = (m1 * m2) / g;
    x = true_mod(x, lcm);

    return std::make_tuple(x, lcm);
}

int main()
{
    long cases;
    scanf(" %ld", &cases);

    for (long i{0}; i < cases; i++)
    {
	long long  a, n, b, m;
	scanf(" %lld", &a);
	scanf(" %lld", &n);
	scanf(" %lld", &b);
	scanf(" %lld", &m);

	std::tuple<__int128, __int128> res =
	    merge_crt((__int128) a, (__int128) n, (__int128) b, (__int128) m);

	if (std::get<0>(res) == 0 && std::get<1>(res) == 0)
	{
	    printf("no solution\n");
	}
	else
	{
	    printf("%lld %lld\n", (long long) std::get<0>(res), (long long) std::get<1>(res));
	}
    }
}

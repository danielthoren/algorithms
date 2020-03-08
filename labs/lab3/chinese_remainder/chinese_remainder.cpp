
#include "extended_euclidean.h"

#include <tuple>

/**
 * Merges two congruence equations using the weak chinese remainder
 * theorem, thus it is assumed that m1, m2 are coprime. With other
 * words, it is assumed that GCD(m1, m2) = 1
 *
 * Both equations e1, e2 are on the form (= is congruence): 
 * x = a (mod m) where e = tuple(a, m) (*1)
 *
 * Because of this assumption we know from Bezouts identity that there
 * is a solution to the following equation:
 * m1*S + m2*T = 1 (*2)
 *
 * When Bezeouts coefficients (S, T) has been found the following
 * expression can be used to get the x in equation (*1):
 * x = a1*m2*T + a2*m1*S (mod m1*m2) (*3)
 *
 * Time complexity: O(log n) (time complexity of extended_euclidean)
 *
 */
template<typename T>
std::tuple<T, T> merge_crt(std::tuple<T, T> e1, std::tuple<T, T> e2)
{
    //Extended euclidean gives <GCD(m1, m2), p, q>
    std::tuple<T, T, T> euclid = extended_euclidean(std::get<1>(e1), std::get<1>(e2));

    T x =
	std::get<0>(e1) * std::get<1>(e2) * std::get<2>(euclid) +
	std::get<0>(e2) * std::get<1>(e1) * std::get<1>(euclid);

    x = true_mod(x, std::get<1>(e1) * std::get<1>(e2));

    return std::make_tuple(x, std::get<1>(e1) * std::get<1>(e2));       
}

int main()
{
    long cases;
    scanf(" %ld", &cases);

    for (long i{0}; i < cases; i++)
    {
	long long a, n, b, m;
	scanf(" %lld", &a);
	scanf(" %lld", &n);
	scanf(" %lld", &b);
	scanf(" %lld", &m);

	std::tuple<long long, long long> res = merge_crt<long long>(std::make_tuple(a,n),
						     std::make_tuple(b,m));

	printf("%lld %lld\n", std::get<0>(res), std::get<1>(res));
    }
}

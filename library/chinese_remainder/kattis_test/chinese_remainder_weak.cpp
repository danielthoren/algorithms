
#include "chinese_remainder.h"

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

	std::pair<__int128, __int128> res =
	    dalg::merge_crt((__int128) a, (__int128) n, (__int128) b, (__int128) m);

	printf("%lld %lld\n", (long long) res.first, (long long) res.second);
    }
}

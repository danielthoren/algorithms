#include "chinese_remainder.h"

#include <vector>
#include <utility>
#include <tuple>
#include <cmath>

using namespace std;

int main()
{
    int cases;
    scanf(" %d", &cases);

    for (int i{0}; i < cases; i++)
    {
	__int128 a1, m1, a2, m2;
	long long k, c;
	
	scanf(" %lld", &k);
	scanf(" %lld", &c);

	if (k == 1)
	{
	    if (c == 1)
		printf("2\n");
	    else if (c == 2)
		printf("1\n");
	    else
		printf("IMPOSSIBLE\n");
	    
	    continue;
	}

	if (c == 1)
	{
	    printf("%lld\n", k + 1);
	    continue;
	}

	a1 = 1;
	m1 = k;
	
	a2 = 0;
	m2 = c;
	
	pair<__int128, __int128> res = merge_crt(a1, m1, a2, m2);

	if (res.first == 0)
	    printf("IMPOSSIBLE\n");
	else
	    printf("%lld\n", (long long) (res.first / c));
	
    }    
}

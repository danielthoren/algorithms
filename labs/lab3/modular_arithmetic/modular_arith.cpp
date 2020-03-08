#include <algorithm>
#include <vector>
#include <limits.h>
#include <functional>
#include <tuple>

#include "extended_euclidean.h"

int main()
{
    long long mod;
    long long ops;

    while (true)
    {
	scanf(" %lld", &mod);
	scanf(" %lld", &ops);

	if (mod == 0 && ops == 0)
	    return 0;

	for (long long i{0}; i < ops; i++)
	{
	    long long x, y;
	    char op;
	
	    scanf(" %lld", &x);
	    scanf(" %c", &op);
	    scanf(" %lld", &y);

	    if (op == '/')
	 {
	     long long res = get_modular_inverse<long long>(y, mod);
	     if (res == -1)
	{
	    printf("%lld\n", res);
	}
		 else
		 {
		     printf("%lld\n", true_mod<long long>(x*res, mod));
		 }
	     }
	     else if (op == '+')
	     {
		 printf("%lld\n", true_mod<long long>(x+y, mod));
	     }
	     else if (op == '-')
	     {
		 printf("%lld\n", true_mod<long long>(x-y, mod));
	     }
	     else if (op == '*')
	     {
		 printf("%lld\n", true_mod<long long>(x*y, mod));
	     }
	 }
     }
}

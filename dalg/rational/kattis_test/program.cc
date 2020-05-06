
#include "rational.h"

using namespace std;
int main()
{

    int cases;

    scanf(" %d", &cases);

    for (int c{0}; c < cases; c++)
    {
	int num1, denum1, num2, denum2;
	char op;

	scanf(" %d", &num1);
	scanf(" %d", &denum1);
	scanf(" %c", &op);	
	scanf(" %d", &num2);
	scanf(" %d", &denum2);
	
	dalg::Rational<long long int> r1{num1, denum1};
	dalg::Rational<long long int> r2{num2, denum2};

	if (op == '+')
	    r1 += r2;
	else if (op == '-')
	    r1 -= r2;
	else if (op == '*')
	    r1 *= r2;
	else if (op == '/')
	    r1 /= r2;

	printf("%s\n",r1.str().c_str());
    }
}

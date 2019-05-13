#include <iostream>
#include "rational.h"

using namespace std;
int main()
{
    std::ios_base::sync_with_stdio(false);

    int cases;
    cin >> cases;

    for (int c{0}; c < cases; c++)
    {
	int num1, denum1, num2, denum2;
	char op;

	cin >> num1 >> denum1 >> op >> num2 >> denum2;
	Rational<int> r1{num1, denum1};
	Rational<int> r2{num2, denum2};

	if (op == '+')
	    r1 += r2;
	else if (op == '-')
	    r1 -= r2;
	else if (op == '*')
	    r1 *= r2;
	else if (op == '/')
	    r1 /= r2;

	cout << r1 << endl;	
    }
}

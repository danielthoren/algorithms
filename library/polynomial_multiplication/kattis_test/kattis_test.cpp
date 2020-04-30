#include "polynomial_multiplication.h"
#include <iostream>

using namespace std;

int main()
{
    int T, order;
    cin >> T >> order;

    for (int p{0}; p < T; p++)
    {
	std::vector<double> poly1, poly2;

	for (int i = 0; i <= order; i++)
	{
	    double in;
	    cin >> in;
	    poly1.push_back(in);
	}

	int order2;
	cin >> order2;

	for (int i = 0; i <= order2; i++)
	{
	    double in;
	    cin >> in;
	    poly2.push_back(in);
	}

	std::vector<int> result{polynomial_multiplication(poly1, poly2)};

	cout << (order + order2) << endl;

	for (int i{0}; i < result.size(); i++)
	    cout  << result.at(i) << " ";

	cout << endl;
    }

    return 0;
}

#define _USE_MATH_DEFINES

#include <vector>
#include <math.h>
#include <complex>
#include <cmath>
#include <iostream>
#include <algorithm>

using namespace std;

vector<complex<double>> FFT(vector<complex<double>> poly, complex<double> w)
{
    if (poly.size() <= 1)
	return poly;

    complex<double> nw{cos(2*M_PI/poly.size()), sin(2*M_PI/poly.size())};
    
    vector<complex<double>> poly_even, poly_uneven;    
    for (int i = 0; i < poly.size()/2; ++i)
    {
	poly_even.push_back(poly.at(i * 2));
	poly_uneven.push_back(poly.at(i * 2 + 1));
    }

    vector<complex<double>> poly_even_res{ FFT(poly_even, w) };
    vector<complex<double>> poly_uneven_res{ FFT(poly_uneven, w) };

    for (int j{0}; j < poly.size()/2 ; ++j)
    {
	poly[j] = poly_even_res[j] + w*poly_uneven_res[j];
	poly[j+poly.size()/2] = poly_even_res[j] - w*poly_uneven_res[j];
	w = w * nw;
    }
    return poly;
}

void pad_with_ones(vector<complex<double>>& poly, int amount)
{
    for (int i = 0; i < amount; i++)
	poly.push_back(1);
}

vector<complex<double>> convalution(vector<complex<double>>& poly1, vector<complex<double>>& poly2)
{    
    reverse(poly1.begin(), poly1.end());
    vector<complex<double>> result;
    
    int overlap = 1;
    int max_overlap = abs(poly1.size() - poly2.size());
    bool turning = false;
    for(int i{0}; i < (poly2.size() + poly1.size()); i++)
    {
	for(int j{0}; j < overlap; j++)
	{	    
	    result.push_back(poly1.at(poly1.size() - j) * poly2.at(j));
	}
	if (overlap >= max_overlap)
	    turning = true;

	if (turning)
	    overlap--;
	else
	    overlap++;
    }
}

int main()
{
    int T, order;
    cin >> T >> order;

    if (T != 1)
	return -1;

    vector<complex<double>> poly1, poly2;

    for (int i = 0; i <= order; i++)
    {
	double in;
	cin >> in;
	poly1.push_back(in);
    }

    order = 0;
    cin >> order;

    for (int i = 0; i <= order; i++)
    {
    	double in;
    	cin >> in;
    	poly2.push_back(in);
    }

    vector<complex<double>> poly1_c = FFT(poly1, 1);
    vector<complex<double>> poly2_c = FFT(poly2, 1);

    vector<complex<double>> result_c{ FFT(poly1_c, poly2_c), 0) };
    vector<double> result;
    
    for (int i = 0; i < result_c.size(); ++i)
    {
	result.push_back(result_c.at(i).real() * result_c.size());
    }
    

    for (auto it : result)
	cout << "Re: " << it << endl;
}

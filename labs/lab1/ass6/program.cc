#define _USE_MATH_DEFINES

#include <vector>
#include <math.h>
#include <complex>
#include <cmath>
#include <iostream>
#include <algorithm>

using namespace std;

vector<complex<double>> FFT(vector<complex<double>> poly, int w)
{
    if (poly.size() <= 1)
	return poly;

    complex<double> nw{cos(w*2*M_PI/poly.size()), sin(w*2*M_PI/poly.size())};
    
    vector<complex<double>> poly_even, poly_uneven;    
    for (int i = 0; i < poly.size()/2; ++i)
    {
	poly_even.push_back(poly.at(i * 2));
	poly_uneven.push_back(poly.at(i * 2 + 1));
    }

    vector<complex<double>> poly_even_res{ FFT(poly_even, w) };
    vector<complex<double>> poly_uneven_res{ FFT(poly_uneven, w) };

    complex<double> x{1};
    for (int j{0}; j < poly.size()/2 ; ++j)
    {
	poly[j] = poly_even_res[j] + x*poly_uneven_res[j];
	poly[j+poly.size()/2] = poly_even_res[j] - x*poly_uneven_res[j];
	
	if (w == -1)
	{
	    poly[j] /= 2;	    /* Dividing every entry in poly by n since this is recursive */
	    poly[j+poly.size()/2] /= 2;
	}
	    
	x = x * nw;
    }
    return poly;
}

int next_power_of_two(int n)
{
    n |= n >> 16;
    n |= n >> 8;
    n |= n >> 4;
    n |= n >> 2;
    n |= n >> 1;

    n++;
    return n;
}

void pad_zeroes(vector<complex<double>>& poly, int target_size)
{
    int orig_size{poly.size()};
    for (int i{0}; i < (target_size - orig_size); i++)
	poly.push_back(0);
}

vector<complex<double>> join_poly(vector<complex<double>>& poly1_c, vector<complex<double>> poly2_c, int target_size)
{
    vector<complex<double>> joined_poly(target_size);
    for (int i{0}; i < target_size; i++)
    {
	joined_poly[i] = poly1_c[i] * poly2_c[i];
    }
    return joined_poly;
}

vector<int> polynomial_multiplication(vector<double> poly1_r, vector<double> poly2_r)
{
    vector<complex<double>> poly1;
    for (double elem : poly1_r)
	poly1.push_back(elem);
    
    int order1 = poly1_r.size() - 1;
    
    vector<complex<double>> poly2;
    for (double elem : poly2_r)
	poly2.push_back(elem);
    
    int order2 = poly2_r.size() - 1;    
    
    int target_size = next_power_of_two(order1 + order2 + 1);
    pad_zeroes(poly1, target_size);
    pad_zeroes(poly2, target_size);

    vector<complex<double>> poly1_c = FFT(poly1, 1);
    vector<complex<double>> poly2_c = FFT(poly2, 1);
    
    vector<complex<double>> joined_poly = join_poly(poly1_c, poly2_c, target_size);

    vector<complex<double>> result_c{ FFT(joined_poly, -1) };
    vector<int> result;
    
    for (int i = 0; i < (order1 + order2 + 1); ++i)
    {
	int tmp = round(result_c.at(i).real());
	result.push_back(tmp);
    }
    return result;
}

int main()
{
    int T, order;
    cin >> T >> order;

    if (T != 1)
	return -1;

    vector<double> poly1, poly2;

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

    vector<int> result{polynomial_multiplication(poly1, poly2)};

    cout << (order + order2) << endl;

    for (int i{0}; i < result.size(); i++)
	cout  << result.at(i) << " ";

    cout << endl;

    return 0;
}

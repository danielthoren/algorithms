#include <math.h>
#include <cmath>
#include <algorithm>

#ifndef POLYNOMIAL_MULTIPLICATION
#error 'polynomial_multiplication.tcc' is not supposed to be included directly. Include 'polynomial_multiplication.h' instead.
#endif

template<typename T>
std::vector<std::complex<T>> FFT(std::vector<std::complex<T>> poly, int w)
{
    if (poly.size() <= 1)
	return poly;

    std::complex<T> nw{cos(w*2*M_PI/poly.size()), sin(w*2*M_PI/poly.size())};
    
    std::vector<std::complex<T>> poly_even, poly_uneven;    
    for (unsigned i = 0; i < poly.size()/2; ++i)
    {
	poly_even.push_back(poly.at(i * 2));
	poly_uneven.push_back(poly.at(i * 2 + 1));
    }

    std::vector<std::complex<T>> poly_even_res{ FFT(poly_even, w) };
    std::vector<std::complex<T>> poly_uneven_res{ FFT(poly_uneven, w) };

    std::complex<T> x{1};
    for (unsigned j{0}; j < poly.size()/2 ; ++j)
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


template<typename T>
void pad_zeroes(std::vector<std::complex<T>>& poly, unsigned target_size)
{
    long unsigned orig_size{poly.size()};
    for (long unsigned i{0}; i < (target_size - orig_size); i++)
	poly.push_back(0);
}


template<typename T>
std::vector<std::complex<T>> join_poly(std::vector<std::complex<T>>& poly1_c,
				       std::vector<std::complex<T>> poly2_c,
				       int target_size)
{
    std::vector<std::complex<T>> joined_poly(target_size);
    for (int i{0}; i < target_size; i++)
    {
	joined_poly[i] = poly1_c[i] * poly2_c[i];
    }
    return joined_poly;
}


template<typename T>
std::vector<int> polynomial_multiplication(std::vector<T> poly1_r, std::vector<T> poly2_r)
{
    std::vector<std::complex<T>> poly1;
    for (T elem : poly1_r)
	poly1.push_back(elem);
    
    int order1 = poly1_r.size() - 1;
    
    std::vector<std::complex<T>> poly2;
    for (T elem : poly2_r)
	poly2.push_back(elem);
    
    int order2 = poly2_r.size() - 1;    
    
    int target_size = next_power_of_two(order1 + order2 + 1);
    pad_zeroes(poly1, target_size);
    pad_zeroes(poly2, target_size);

    std::vector<std::complex<T>> poly1_c = FFT(poly1, 1);
    std::vector<std::complex<T>> poly2_c = FFT(poly2, 1);
    
    std::vector<std::complex<T>> joined_poly = join_poly(poly1_c, poly2_c, target_size);

    std::vector<std::complex<T>> result_c{ FFT(joined_poly, -1) };
    std::vector<int> result;
    
    for (int i = 0; i < (order1 + order2 + 1); ++i)
    {
	int tmp = round(result_c.at(i).real());
	result.push_back(tmp);
    }
    return result;
}

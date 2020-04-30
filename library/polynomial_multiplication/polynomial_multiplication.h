#include <vector>
#include <complex>

#ifndef POLYNOMIAL_MULTIPLICATION
#define POLYNOMIAL_MULTIPLICATION

/**
 * Implementation of FFT (Fast Fourier Transform) for polynomials.
 *
 * Complexity: O(n log n)
 *
 * poly: The polynomial to transform
 * w   : if 1 then FFT else if -1 then inverse FFT
 */
template<typename T>
std::vector<std::complex<T>> FFT(std::vector<std::complex<T>> poly, int w);

/**
 * Returns the next power of two given the number n
 *
 * n: the number 
 */
int next_power_of_two(int n);

/**
 * Pads zeroes in the std::vector so that it becomes the target size
 *
 * poly       : The vector to pad
 * target_size: The target size
 */
template<typename T>
void pad_zeroes(std::vector<std::complex<T>>& poly, unsigned target_size);

/**
 * Multiplying the polynomials FFT representations FFT(A * B) = FFT(A) * FFT(B)
 *
 * poly1_c: Polynomial A
 * poly2_c: Polynomial B
 * target_size: The target size of the polynomials
 * return: The multiplied polynomials FFT 
 */
template<typename T>
std::vector<std::complex<T>> join_poly(std::vector<std::complex<T>>& poly1_c,
					    std::vector<std::complex<T>> poly2_c,
					    int target_size);


/**
 * Performs polynomial multiplication by using the following properties of DFT
 * DFT(A * B) = DFT(A) * DFT(B) => A * B = I_DFT( DFT(A) * DFT(B) )
 *
 * Polygons are represented as vectors where the index is represents
 * the order of the variable and the number on each index represents
 * the number multiplied with that order variable:
 *
 * 1 * poly[0] + x * poly[1] + x^2 * poly[2] ....
 * 
 * Complexity: O(n log n)
 *
 * poly1_r: Polynomial 1 in time domain
 * poly2_r: Polynomial 2 in time domain
 * return : Resulting polynomial (rounded to nearest integer) in time domain
 */
template<typename T>
std::vector<int> polynomial_multiplication(std::vector<T> poly1_r,
					   std::vector<T> poly2_r);


#include "polynomial_multiplication.tcc"

#endif

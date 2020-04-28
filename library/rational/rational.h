#include <string>
#include "extended_euclidean.h"

#ifndef RATIONAL_NUM_H
#define RATIONAL_NUM_H

/**
 * Author: Daniel Thorén
 *
 * Class that represents a rational number on the form a/b
 * There are various operations that can be performed on a rational number 
 * =,+,-,*,--,++,-=,+=,*=,<,<=,>,>=,==,!=
 *
 * There are also functions to calculate the greatest and lowest
 * common denominator.
 *
 * Template type must be of numberal type
 *
 */
template<typename T>
class Rational
{
public:    
    Rational(T numerator = 0, T denominator = 1) :
	numerator{numerator}, denominator{denominator}
	{
	    format();
	}

    Rational(Rational<T> const& other) :
	numerator{other.numerator}, denominator{other.denominator}
	{
	    format();
	}
    
    /*
     * All increment and decrement operations add/substract 1 to/from
     * this arithmetic numver. The number is formatted afterwards.
     *
     * Time complexity: O( log(n) )
     *
     * return: This rational number
     */
    Rational<T>& operator++();
    Rational<T> operator++(int);
    Rational<T>& operator--();
    Rational<T> operator--(int);

    /*
     * All arithmetic operations does what one would expect from such
     * operations. After performing the operation this rational number
     * is formatted
     *
     * Time complexity: O( log(n) )
     *
     * return: This rational number
     */    
    Rational<T> operator-(Rational<T> const& other) const;
    Rational<T>& operator-=(Rational<T> const& other);
    Rational<T> operator+(Rational<T> const& other) const;
    Rational<T>& operator+=(Rational<T> const& other);    
    Rational<T> operator/(Rational<T> const& other) const;
    Rational<T>& operator/=(Rational<T> const& other);
    Rational<T>& operator*=(Rational<T> const& other);
    Rational<T> operator*(Rational<T> const& other) const;

    /*
     * Dereference operator, returns the value of this rational number
     * by dividing numerator with denominator
     *
     * Time complexity: O(1)
     *
     * Template type should be floating point of the desired precision
     *
     * return: (FT) x / (FT) y
     */
    template <typename FT>
    FT operator*() const;
    Rational<T>& operator=(Rational<T> const& other);

    /**
     * All comparator operations compare the given rational number
     * with this rational number in the mathmatical sense.
     *
     * Time complexity: O(1)
     *
     * other : Other rational number to compare with
     *
     * return: The result of the comparison
     */
    bool operator==(Rational<T> const& other) const;
    bool operator!=(Rational<T> const& other) const;
    bool operator<(Rational<T> const& other) const;
    bool operator<=(Rational<T> const& other) const;
    bool operator>(Rational<T> const& other) const;
    bool operator>=(Rational<T> const& other) const;

    /**
     * Returns the rational number as a string formatted in the
     * following way:
     *
     * return: x / y
     */
    std::string str() const;

    /**
     * Uses the extended euclidean algorithm to get gcd(x, y)
     *
     * Time complexity: O( log(n) )
     *
     * Template must be of integer type
     *
     * x     : integral number 1
     * y     : integral number 2
     * 
     * return: gcd(x, y)
     */
    T greatest_common_denominator(T x, T y) const;

    /**
     * Uses the gcd(x,y) function to get lcd(x,y) in the following way:
     * lcd(x,y) = (x*y) / gcd(x,y)
     *
     * Time complexity: O( log(n) )
     *
     * Template must be of integer type
     *
     * x     : integral number 1
     * y     : integral number 2
     * 
     * return: lcd(x, y)
     */
    T lowest_common_denominator(T x, T y) const;

    /**
     * Formats the rational number in the following way:
     *
     * 0 / y   -> 0 / 1  (if numerator is 0 then denominator turns to 1)
     * x / -y  -> -x / y (if denominator is negative, move negation to numerator)
     * 2x / 2y -> x / y  (divide numerator and denominator with gcd(x,y))
     *
     * Time complexity: O( log(n) )
     */
    void format();

private:
    T numerator;   //Täljare
    T denominator; //Nämnare
};

template<typename T>
std::ostream& operator<<(std::ostream& os, Rational<T> const& r);

/**
 * Accepts rational numbers on the following form and writes it to the
 * given rational number. If the format is wrong the failbit is set,
 * the rational number is unaltered and the stream is returned in its
 * current state.
 *
 * Accepted input: 'x / y'
 *
 * Time complexity: O( log(n) )
 */
template<typename T>
std::istream& operator>>(std::istream& is, Rational<T>& r);

#include "rational.tcc"

#endif

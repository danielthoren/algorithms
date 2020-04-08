#include <string>

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

    Rational<T> operator+(Rational<T> const& other) const;
    Rational<T>& operator+=(Rational<T> const& other);

    /*
     * Post-increment
     */
    Rational<T>& operator++();

    /*
     * Pre-increment
     */
    Rational<T> operator++(int);
    Rational<T> operator-(Rational<T> const& other) const;
    Rational<T>& operator-=(Rational<T> const& other);

    /*
     * Post-decrement
     */
    Rational<T>& operator--();

    /*
     * Pre-decrement
     */
    Rational<T> operator--(int);
    Rational<T> operator/(Rational<T> const& other) const;
    Rational<T>& operator/=(Rational<T> const& other);
    Rational<T>& operator*=(Rational<T> const& other);
    Rational<T> operator*(Rational<T> const& other) const;

    /*
     * Dereference operator, returns the value of this rational number
     * by dividing numerator with denominator
     */    
    T operator*() const;
    Rational<T>& operator=(Rational<T> const& other);
    bool operator==(Rational<T> const& other) const;
    bool operator!=(Rational<T> const& other) const;
    bool operator<(Rational<T> const& other) const;
    bool operator<=(Rational<T> const& other) const;
    bool operator>(Rational<T> const& other) const;
    bool operator>=(Rational<T> const& other) const;
    
    std::string str() const;

 
    T greatest_common_denominator(T x, T y) const;
    T lowest_common_denominator(T x, T y) const;
    void format();
    
    T numerator;   //Täljare
    T denominator; //Nämnare
};

template<typename T>
std::ostream& operator<<(std::ostream& os, Rational<T> const& r);

#include "rational.tcc"

#endif
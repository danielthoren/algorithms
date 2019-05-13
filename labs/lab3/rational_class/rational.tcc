#ifndef RATIONAL_NUM_H
#error 'rational.gch' is not supposed to be included directly. Include 'rational.h' instead.
#endif

#include <sstream>
#include <cmath>

template<typename T>
Rational<T> Rational<T>::operator+(Rational<T> const& other) const
{
    Rational tmp{*this};
    tmp += other;
    tmp.format();
    return tmp;
}

template<typename T>
Rational<T>& Rational<T>::operator+=(Rational<T> const& other)
{
    T lcd{ lowest_common_denominator(std::abs(other.denominator),
				     std::abs(denominator)) };
    //lcd is the final denominator, thus to get the multiple for the numerator
    //this needs to be divided with the current denominator
    numerator = numerator * (lcd / denominator) +
	other.numerator * (lcd / other.denominator);
    denominator = lcd;

    format();
    
    return *this;
}

/*
 * Post-increment
 */
template<typename T>
Rational<T>& Rational<T>::operator++()
{
    numerator += denominator;
    format();
    return *this;
}

/*
 * Pre-increment
 */
template<typename T>
Rational<T> Rational<T>::operator++(int)
{
    Rational<T> tmp{*this};
    tmp++;
    tmp.format();
    return tmp;
}

template<typename T>
Rational<T> Rational<T>::operator-(Rational const& other) const
{
    Rational tmp{*this};
    tmp += other;
    tmp.format();
    return tmp;
}

template<typename T>
Rational<T>& Rational<T>::operator-=(Rational const& other)
{    
    T lcd{ lowest_common_denominator(std::abs(other.denominator),
				     std::abs(denominator)) };
    //lcd is the final denominator, thus to get the multiple for the numerator
    //this needs to be divided with the current denominator
    numerator = numerator * (lcd / denominator) -
	other.numerator * (lcd / other.denominator);
    denominator = lcd;
    format();
    return *this;
}

/*
 * Post-decrement
 */
template<typename T>
Rational<T>& Rational<T>::operator--()
{
    numerator -= denominator;
    format();
    return *this;
}

/*
 * Pre-decrement
 */
template<typename T>
Rational<T> Rational<T>::operator--(int)
{
    Rational tmp{*this};
    tmp--;
    return tmp;
}

template<typename T>
Rational<T> Rational<T>::operator/(Rational<T> const& other) const
{
    Rational tmp{*this};
    tmp /= other;
    tmp.format();
    return tmp;
}

template<typename T>
Rational<T>& Rational<T>::operator/=(Rational<T> const& other)
{
    T num = numerator * other.denominator;
    denominator *= other.numerator;
    numerator = num;
    format();
    return *this;
}

template<typename T>
Rational<T>& Rational<T>::operator*=(Rational<T> const& other)
{
    numerator *= other.numerator;
    denominator *= other.denominator;
    format();
    return *this;
}

template<typename T>
Rational<T> Rational<T>::operator*(Rational<T> const& other) const
{    
    Rational<T> tmp{numerator * other.numerator, denominator * other.denominator};
    tmp.format();
    return tmp;
}

template<typename T>
T Rational<T>::operator*() const
{
    return numerator / denominator;
}

template<typename T>
Rational<T>& Rational<T>::operator=(Rational<T> const& other)
{
    numerator = other.numerator;
    denominator = other.denominator;
    return *this;
}

template<typename T>
bool Rational<T>::operator==(Rational<T> const& other) const
{
    return numerator == other.numerator &&
	denominator == other.denominator;
}

template<typename T>
bool Rational<T>::operator!=(Rational<T> const& other) const
{
    return !(other == *this);
}

template<typename T>
bool Rational<T>::operator<(Rational<T> const& other) const
{
    return (numerator / denominator) < (other.numerator / other.denominator);
}

template<typename T>
bool Rational<T>::operator<=(Rational<T> const& other) const
{
    return (numerator / denominator) <= (other.numerator / other.denominator);
}

template<typename T>
bool Rational<T>::operator>(Rational<T> const& other) const
{
    return !(*this <= other);
}

template<typename T>
bool Rational<T>::operator>=(Rational<T> const& other) const
{
    return !(*this < other);
}

template<typename T>
std::string Rational<T>::str() const
{
    std::stringstream ss;
    ss << numerator << " / " << denominator;
    return ss.str();
}

// template<typename T>
// T Rational<T>::greatest_common_denominator(T x, T y) const
// {
//     if (x == 0 || y == 0)
// 	return 0;

//     if (x == y)
// 	return x;

//     if (x > y)
// 	return greatest_common_denominator(x - y, y);
//     return greatest_common_denominator(x, y - x);
// }

template<typename T>
T Rational<T>::greatest_common_denominator(T x, T y) const
{
    if (y == 0)
	return x;

    return greatest_common_denominator(y, x % y);
}

template<typename T>
T Rational<T>::lowest_common_denominator(T x, T y) const
{
    return (x*y) / greatest_common_denominator(x, y);
}

template<typename T>
void Rational<T>::format()
{
    if (numerator == 0)
	return;
    
    if (denominator < 0)
    {
	denominator = std::abs(denominator);
	if (numerator > 0)
	    numerator = -numerator;
	else
	    numerator = std::abs(numerator);
    }
    
    T gcd{ greatest_common_denominator( std::abs(numerator),
					     std::abs(denominator)) };
    numerator = numerator / gcd;
    denominator = denominator / gcd;       
}

template<typename T>
std::ostream& operator<<(std::ostream& os, Rational<T> const& r)
{
    os << r.str();
    return os;
}

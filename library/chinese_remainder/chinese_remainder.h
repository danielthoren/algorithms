#include <vector>
#include <utility>
#include <tuple>

#include "extended_euclidean.h"

#ifndef CHINESE_REMAINDER
#define CHINESE_REMAINDER

/**
 * Author: Daniel Thorén
 *
 * Merges two congruence equations using the weak chinese remainder
 * theorem, thus it is assumed that m1, m2 are coprime. With other
 * words, it is assumed that GCD(m1, m2) = 1
 *
 * Both equations e1, e2 are on the form (= is congruence): 
 * x = a (mod m) where e = tuple(a, m) (*1)
 *
 * Because of this assumption we know from Bezouts identity that there
 * is a solution to the following equation:
 * m1*S + m2*T = 1 (*2)
 *
 * When Bezeouts coefficients (S, T) has been found the following
 * expression can be used to get the x in equation (*1):
 * x = a1*m2*T + a2*m1*S (mod m1*m2) (*3)
 *
 * Time complexity: O(log n) (time complexity of extended_euclidean)
 *
 */
template<typename T>
std::pair<T,T> merge_crt(T a1, T m1, T a2, T m2);

/**
 * Author: Daniel Thorén
 *
 * Merges two congruence equations using the strong chinese remainder
 * theorem, thus it is assumed that m1, m2 are not coprime. With other
 * words, it is assumed that GCD(m1, m2) != 1
 *
 * Both equations a1, m1, a2, m2 are on the form (= is congruence): 
 * x = 1a (mod 1m) (*1)
 *
 * If the following is true then there exists a solustion, otherwise not
 * gcd(m1, m2) = g
 * a1 = a2 mod g (where = is congruence) =>
 * a1 mod g == a2 mod g
 * If there is not solution then the function returns a tuple with only 0 in it
 * tuple<T, T>(0, 0)
 *
 * If a solution exists we know from Bezouts identity that there
 * is a solution to the following equation:
 * m1*S + m2*T = g <=>
 * (m1*S)/g + (m2*T)/g = 1 (*2)
 *
 * When Bezeouts coefficients (S, T) has been found the following
 * expression can be used to get the x in equation (*1):
 * x = (a1 * m2 * T) / g + (a2 * m1 * S) (*3)
 *
 * The smallest solution to the problem can be found by modding x from (*3)
 * with lcm(m1, m2):
 * lcm(m1, m2) = (m1 * m2) / gcd(m1, m2) = l
 * x = x mod l
 *
 * Time complexity: O(log n) where n is max(m1, m2)
 *                           (time complexity of extended_euclidean)
 *
 */
template<typename T>
std::pair<T,T> merge_crt_strong(T a1, T m1, T a2, T m2);



/**
 * Merges all modular equations into one modular equation.
 *
 * Equations {a1, m1} are on the form (= is congruence): 
 * x = a1 (mod m1) (*1)
 *
 * See comment over merge_crt_strong for more information.
 *
 * Time Complexity: O(e * log n) n = max(m1, m2)
 *                               e = equations.size()
 */
template<typename T>
std::pair<T, T> merge_mod_eq_strong(std::vector<std::pair<T,T>> equations);

#include "chinese_remainder.tcc"

#endif

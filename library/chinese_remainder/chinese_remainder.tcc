

template<typename T>
std::pair<T,T> merge_crt(T a1, T m1, T a2, T m2)
{
    //Extended euclidean gives <GCD(m1, m2), S, T
    std::tuple<T, T, T> euclid = extended_euclidean(m1, m2);

    T a0 =
        a1 * m2 * std::get<2>(euclid) +
        a2 * m1 * std::get<1>(euclid);

    T prod = m1 * m2;

    //true_mod always returns positive
    T x = true_mod(a0, prod);

    return {x, prod};
}

template<typename T>
std::pair<T,T> merge_crt_strong(T a1, T m1, T a2, T m2)
{

    //Calculating GCD(m1, m2) to check if there is a solution
    std::tuple<T, T, T> gcd_euclid = extended_euclidean(m1, m2);
    T g = std::get<0>(gcd_euclid);

    //If the following condition is not met then there is no solution:
    //gcd(m1, m2) = g
    //a1 = a2 mod g (where = is congruence)
    if (true_mod(a2, g) != true_mod(a1, g))
    {
	return {0, 0};
    }
    
    //Extended euclidean gives <GCD(m1/g, m2/g), S, T
    //We know that there is a solution to the following equation:
    //m1*S + m2*T = g <=>
    //m1*S/g + m2*T/g = 1
    std::tuple<T, T, T> euclid = extended_euclidean(m1/g, m2/g);
    T s = std::get<1>(euclid);
    T t = std::get<2>(euclid);

    T x =
	a1 * (m2 / g) * t +
	a2 * (m1 / g) * s;

    //Find the smallest possible solution by modding x with lcm(m1, m2)
    T lcm = (m1 * m2) / g;
    x = true_mod(x, lcm);

    return {x, lcm};
}


template<typename T>
std::pair<T, T> merge_mod_eq_strong(std::vector<std::pair<T,T>> equations)
{
    std::pair<T,T> result = merge_crt_strong(equations[0].first, equations[0].second,
					     equations[1].first, equations[1].second);    

    for (int eq{2}; eq < equations.size(); eq++)
    {
	result = merge_crt_strong(result.first, result.second,
				  equations[eq].first, equations[eq].second);
    }

    return result;
}

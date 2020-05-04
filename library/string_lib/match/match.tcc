#include<sstream>

#ifndef MATCH
#error 'match.tcc' is not supposed to be included directly. Include 'match.h' instead.
#endif

template<typename T>
std::vector<unsigned> dalg::Match<T>::generate_prefix(T& pattern)
{
    std::vector<unsigned> prefix{0};
    unsigned i{0};
    for (unsigned pos{1}; pos < pattern.size(); pos++)
    {
	while (i > 0 && pattern[i] != pattern[pos] && i < pattern.size())
	    i = prefix[i - 1];

	if (pattern[i] == pattern[pos])
	    i += 1;

	prefix.push_back(i);
    }
    return prefix;
}

template<typename T>
std::vector<unsigned> dalg::Match<T>::match(T& data)
{
    std::vector<unsigned> matches{};

    unsigned k{0};
    for (unsigned j{0}; j <= data.size(); j++)
    {
	//if current letter is a match
	if (pattern[k] == data[j])
	{
	    //Pattern has been found
	    if (k == (pattern.size() - 1))
	    {		
		matches.push_back(j - k);
		k = prefix[k];
	    }
	    //Not match yet, continue checking
	    else
	    {
		k++;
	    }
	}
	//If missmatch
	else if (k != 0)
	{
	    k = prefix[k - 1];
	    j--; //Staying on the same letter in data
	}
    }
    return matches;
}

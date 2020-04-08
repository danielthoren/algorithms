#include <iostream>

/**
 * Generates the prefix for the search pattern. 
 *
 * Time complexity: O(m) where m is the length of the pattern
 */
template<typename T>
std::vector<int> generate_prefix(T& pattern)
{
    std::vector<int> prefix{0};
    int i{0};
    for (int pos{1}; pos < pattern.size(); pos++)
    {
	while (i > 0 && pattern[i] != pattern[pos] && i < pattern.size())
	    i = prefix[i - 1];

	if (pattern[i] == pattern[pos])
	    i += 1;

	prefix.push_back(i);
    }
    return prefix;
}

/**
 * Author: Daniel Thorén
 *
 * Implementation of the KMP (Knuth-Morris-Pratt) algorithm. It
 * searches the string by generating a prefix for the pattern. The
 * prefix details which position in the string to jump to the correct
 * position when a match is found and when one is'nt found. This
 * greatly optimizes the search by not revisiting unnecessary letters
 * in the search string.
 *
 * Time complexity: O(n) where n is the length of the search string
 *
 * pattern: The pattern to search for
 * data   : The data to search in
 * return : Vector with start positions of all matches
 */
template<typename T>
std::vector<int> string_matching(T& pattern, T& data)
{
    std::vector<int> prefix{ generate_prefix(pattern) };
    std::vector<int> matches{};

    int k{0};
    for (int j{0}; j <= data.size(); j++)
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

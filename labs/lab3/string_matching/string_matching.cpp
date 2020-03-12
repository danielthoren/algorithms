#include <iostream>
#include <string>
#include <vector>

/**
 * Generates the prefix for the search pattern. 
 *
 * Time complexity: O(m) where m is the length of the pattern
 */
std::vector<int> generate_prefix(std::string& pattern)
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
 */
std::vector<int> string_matching(std::string& pattern, std::string& data)
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

int main()
{
    std::ios_base::sync_with_stdio(false);
    std::cin.tie(NULL);
    
    std::string pattern;
    std::string data;
    while (std::getline(std::cin, pattern))
    {
	std::getline(std::cin, data);
	
	std::vector<int> matches{ string_matching(pattern, data) };
	
	if (matches.size() > 0)
	    std::cout << matches[0];
	
	for (int n{1}; n < matches.size(); n++)
	    std::cout << " " << matches[n];
	std::cout << std::endl;
    }

    return 0;
}

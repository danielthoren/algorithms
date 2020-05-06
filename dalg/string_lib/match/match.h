#ifndef MATCH
#define MATCH

#include<iostream>
#include<string>
#include<vector>

namespace dalg
{

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
     * The same prefix can be used to search multiple texts for the pattern.
     *
     * Template type T must support operator[] and .size() operations
     * The return type of operator[] must support == operator
     */
    template<typename T = std::string>
    class Match
    {
    public:

	Match(T pattern) : prefix{ generate_prefix(pattern) },
			   pattern{pattern}
	    {}

	/**
	 * The algorithm that uses the prefix to search for the pattern.
	 *
	 * Time complexity: O(n) where n is the length of the search string
	 *
	 * data   : The data to search in
	 * return : Vector with start positions of all matches
	 */
	std::vector<unsigned> match(T& data);

    private:

	/**
	 * Generates the prefix for the search pattern. 
	 *
	 * Time complexity: O(m) where m is the length of the pattern
	 */
	std::vector<unsigned> generate_prefix(T& pattern);

	std::vector<unsigned> prefix;
	T pattern;
    };
}

#include "match.tcc"

#endif

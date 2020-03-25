#include <vector>

/**
 * Author: Daniel Thorén
 *
 * This function searches the given text for all of the patterns and
 * returns a vector containing one vector for each pattern (at the
 * same indexes). Each such vector contians an integer per match
 * detailing the position of the match (first letter of the match)
 *
 * Template type T must support operator[] and .size() operations
 * The return type of operator[] must support == operator
 *
 * Time complexity  : O( n + pn + m )
 * Memory complexity: O(pn)
 *                    n  = len(text)
 *                    pn = sum[i=0]( len( patterns[i] ) )
 *                    m  = count( matches )
 *
 * patterns: A reference to the patterns to be searched for
 * text    : The text to search
 * return  : Vector containing positions of all matches. Has the
 *           following format: 
 *           vector< vector< matches of pattern 0 >, vector< matches of pattern 1 >, ...>
 */
template<typename T>
std::vector<std::vector<int>>
multimach_search(std::vector<T> const& patterns, T const& text);


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
 * Template type T must support operator[] and .size() operations
 * The return type of operator[] must support == operator
 *
 * Time complexity: O(n) where n is the length of the search string
 *
 * pattern: The pattern to search for
 * data   : The data to search in
 * return : Vector with start positions of all matches
 */
template<typename T>
std::vector<int> string_matching(T& pattern, T& data);

#include "string_matching.tcc"
#include "string_multimatching.tcc"

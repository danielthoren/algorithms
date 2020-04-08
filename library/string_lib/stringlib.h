#include <vector>

#ifndef STRING_LIB
#define STRING_LIB
/**
 * Inserter following this pattern:
 *
 * Vector containing positions of all matches. Has the
 *           following format: 
 *           vector< vector< matches of pattern 0 >, vector< matches of pattern 1 >, ...>
 */
template<typename T = int>
struct insert_vec{
    using res_type = std::vector<std::vector<T>>;

    insert_vec(T initial_size = 0):
	result(initial_size)
	{};
    
    void insert(T pattern, T pos)
	{
	    result[pattern].push_back(pos);
	}

    res_type result;
};


/**
 * Inserter following this pattern:
 *
 * Vector containing positions of all matches. Has the
 *           following format: 
 *           vector< pair<pattern, position>, ...>
 */
template<typename T = int>
struct insert_pair{
    using res_type = std::vector<std::pair<T, T>>;

    insert_pair(T initial_size = 0):
	result{}
	{};    
    
    void insert(T pattern, T pos)
	{
	    result.push_back( {pattern, pos} );
	}

    res_type result;
};


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
 * Template type INSERT is used for policy pattern to customize output format. 
 * Policy must follow this pattern:
 *
 * struct NAME {
 *     using res_type = wanted format
 *
 *     void insert(int pattern, int pos); //inserts data into container
 *
 *     res_type result;
 *};
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
template<typename T , typename CONTAINER = insert_vec<T>>
auto string_multi_matching(std::vector<T> const& patterns, T const& text)
    -> decltype( std::declval<CONTAINER>().insert(10, 10),
    	         typename CONTAINER::res_type{});


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

#endif

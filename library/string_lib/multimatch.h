
#include<sstream>
#include<iostream>
#include<string>

#ifndef MULTIMATCH
#define MULTIMATCH

template<typename T = std::string>
class Multimatch
{
private:
    struct Node
    {
	std::vector<int> word_done;
	char letter;
	int parent;
	std::map<char, int> next;
	int reset;
    };
   
public:    
    Multimatch(std::vector<T> const& patterns) : trie{ build_trie(patterns) }
	{
	    build_automaton();
	}


    /**
     * Inserter following this pattern:
     *
     * Vector containing positions of all matches. Has the
     *           following format: 
     *           vector< vector< matches of pattern 0 >, vector< matches of pattern 1 >, ...>
     */
    template<typename IT = int>
    struct insert_vec;

    /**
     * Inserter following this pattern:
     *
     * Vector containing positions of all matches. Has the
     *           following format: 
     *           vector< pair<pattern, position>, ...>
     */
    template<typename IT = int>
    struct insert_pair;

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
    template<typename CONTAINER = insert_vec<int>>
    auto string_multi_matching(T const& text)
	-> decltype( std::declval<CONTAINER>().insert(10, 10),
		     typename CONTAINER::res_type{});

private:

    /**
     * Builds a trie from the given patterns. The trie is stored as a
     * vector of Nodes, each node contains a map that maps characters to
     * integers which represent node positions in the vector.
     *
     * Time complexity: O( sum(p) ) 
     * Memory complexity: O( m*v )
     * where p is the length of an individual pattern and v is the number of verticies
     *
     * patterns: Vector containing all the search patterns
     * return  : Vector containing the trie
     */
    std::vector<Node> build_trie(std::vector<T> const& patterns);

    /**
     * This functions searches for the error edge of the current node by
     * following the error-edges of the parent and then trying to search
     * forward
     *
     * trie: The trie to build into an automata
     * curr: the node to find the error edge of
     */
    int search_backward_error(std::vector<Node>& trie, int curr);

    /**
     * Builds a finite state automaton from the tiven trie by setting the
     * reset edges of all nodes in the trie. A reset edge leads to a node
     * with the same prefix and is used when there is no match in the
     * current node.
     * OBS modifies the trie
     *
     * Time complexity: O( n*log(n) ) n = nodes
     *
     * trie: Reference to the trie, this is modified
     */
    void build_automaton();
    
    std::vector<Node> trie;
};

#include "multimatch.tcc"

#endif

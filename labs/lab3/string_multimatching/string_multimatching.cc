#include<vector>
#include<map>
#include<string>
#include<algorithm>
#include<iostream>
#include<sstream>
#include<queue>
#include<limits>
#include<climits>
#include<stack>

struct Node
{
    std::vector<int> word_done;
    char letter;
    int parent;
    std::map<char, int> next;
    int reset;
};

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
std::vector<Node> build_trie(std::vector<std::string> const& patterns)
{
    std::vector<Node> trie{ Node{{}, -1, 0, {}, -1} };
    int curr{0};
    
    for (int p{0}; p < patterns.size(); p++)
    {
	for (int l{0}; l < patterns[p].size(); l++)
	{
	    //If there is no edge from the current node with the next letter then
	    //add a new node and a edge to that node. Move curr to the new node
	    if (trie[curr].next.find(patterns[p][l]) == trie[curr].next.end())
	    {
		//Adding new node for letter l
		trie.push_back( Node{{}, patterns[p][l], curr,{}, -1} );

		//Creating vertex from current node to new node
		trie[curr].next[patterns[p][l]] = trie.size() - 1;
		//Stepping forward to the new node in the graph
		curr = trie.size() - 1;
	    }
	    //If there already is a edge from the current node with the next letter,
	    //move curr to that node
	    else
	    {
		curr = trie[curr].next[patterns[p][l]];
	    }

	    if (l == patterns[p].size() - 1)
	    {
		trie[curr].word_done.push_back(p);
	    }
	}	    
	//Reset curr to root between every new pattern
	curr = 0;
    }
    return trie;
}

int search_backward_error(std::vector<Node>& trie, int curr)
{
    char ch = trie[curr].letter;

    int prev = curr;    
    int parent = trie[curr].parent;
    curr = trie[parent].reset;
    
    //Searching backwards through trie to find previous reset edge
    //that matches the prefix
    while (prev != 0)
    {
	auto it = trie[curr].next.find(ch);
	if (it != trie[curr].next.end())
	{
	    return it->second;
	}
	else if (curr == 0)
	{
	    return 0;
	}

	prev = curr;
	curr = trie[curr].reset;
    }
    return 0;
}

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
void build_automaton(std::vector<Node>& trie)
{
    //initialize root and its direct neighbours
    trie[0].reset = 0;
    for (auto it : trie[0].next)
    {
	trie[it.second].reset = 0;
    }

    
    std::queue<int> search_queue{};
    search_queue.push(0);

    while (!search_queue.empty())
    {
	int curr = search_queue.front();
	search_queue.pop();

	//Add all neightbours to the queue
	for (auto it : trie[curr].next)
	{
	    search_queue.push(it.second);
	}
	
	int res = search_backward_error(trie, curr);
	if (res != curr)
	{
	    trie[curr].reset = res;

	    //If the new reset edge leads to a leaf node then add the
	    //patterns matching at that node to the current node so
	    //that theese words are not missed
	    for (int w : trie[res].word_done)
	    {		
		trie[curr].word_done.push_back(w);
	    }
	}
    }
}

/**
 * This function searches the given text for all of the patterns and
 * returns a vector containing one vector for each pattern (at the
 * same indexes). Each such vector contians an integer per match
 * detailing the position of the match (first letter of the match)
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
std::vector<std::vector<int>>
multimach_search(std::vector<std::string> const& patterns, std::string const& text)
{
    //Build trie from the patterns
    std::vector<Node> trie = build_trie(patterns);
    //Construct automaton from the trie
    build_automaton(trie);
    
    std::vector<std::vector<int>> matches(patterns.size());

    int curr = 0;

    for (long pos{0}; pos < text.size(); pos++)
    {
	char ch = text[pos];
	//If the current node has an edge with the current letter,
	//follow that edge
	auto it = trie[curr].next.find(ch);
	if (it != trie[curr].next.end())
	{
	    curr = it->second;
	}
	//If there is no edge for the char in the current node then
	//follow parents reset edge and look for forward edge that
	//matches ch there. Repeate this until matching forward edge
	//is found or until curr node is root
	else
	{	    
	    while (curr != 0)
	    {
		curr = trie[curr].reset;

		auto it = trie[curr].next.find(ch);
		if (it != trie[curr].next.end())
		{
		    curr = it->second;
		    break;
		}
	    }	    
	}

	//If curr node is an end node then register matches
	if (trie[curr].word_done.size() != 0)
	{
	    for (int m : trie[curr].word_done)
	    {
		matches[m].push_back(pos - patterns[m].size() + 1);
	    }
	}
    }
    return matches;
}

int main()
{
    std::ios_base::sync_with_stdio(false);
    std::cin.tie(NULL);
    
    int cases;

    while (std::cin >> cases)
    {

	std::vector<std::string> patterns{};
	std::string pattern{};
	std::getline(std::cin, pattern);
	for (int c{0}; c < cases; c++)
	{
	    std::getline(std::cin, pattern);
	    patterns.push_back(pattern);
	}

	std::string text{};
	std::getline(std::cin, text);

	std::vector<std::vector<int>> res = multimach_search(patterns, text);

	for (int p{0}; p < res.size(); p++)
	{
	    for (int m{0}; m < res[p].size(); m++)
	    {
		std::cout << res[p][m] << " ";
	    }
	    std::cout << std::endl;
	}
    }
    return 0;
}

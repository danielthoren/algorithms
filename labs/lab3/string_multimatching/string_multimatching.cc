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
    int word_done;
    char letter;
    int parent;
    std::map<char, int> next;
    std::map<char, int> reset;
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
std::vector<Node> build_trie(std::vector<std::string>& patterns)
{
    std::vector<Node> trie{ Node{-1, -1, 0, {}, {}} };
    int curr{0};
    
    for (unsigned p{0}; p < patterns.size(); p++)
    {
	for (unsigned l{0}; l < patterns[p].size(); l++)
	{
	    //If there is no edge from the current node with the next letter then
	    //add a new node and a edge to that node. Move curr to the new node
	    if (trie[curr].next.find(patterns[p][l]) == trie[curr].next.end())
	    {
		//Adding new node for letter l
		trie.push_back( Node{-1, patterns[p][l], curr,{}, {}} );

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
		trie[curr].word_done = p;
	    }
	}	    
	//Reset curr to root between every new pattern
	curr = 0;
    }

    return trie;
}

int search_forward_error(std::vector<Node>& trie, int curr, std::stack<char> prefix)
{
    while (!prefix.empty())
    {
	char curr_ch = prefix.top();
	prefix.pop();
	auto it = trie[curr].next.find(curr_ch);

	//If the current node has a next edge that matches prefix,
	//move to that node else abort the forward search
	if (it != trie[curr].next.end())
	{
	    curr = it->second;
	}
	else
	{
	    return -1;
	}
    }
    return curr;
}

int search_backward_error(std::vector<Node>& trie, int curr, char ch)
{

    //Stack used to keep track of current prefix
    std::stack<char> prefix{};
    prefix.push(ch);
    int prev = curr;
    curr = trie[curr].parent;
    
    //Searching backwards through trie to find previous reset edge
    //that matches the prefix
    while (prev != 0)
    {
	char curr_ch = prefix.top();

	//If current prefix symbol exists in the current node or if
	//the search has reached the root node, start searching
	//forward to se if the entire prefix matches
	auto it = trie[curr].reset.find(ch);
	if (it != trie[curr].reset.end() || curr == 0)
	{
	    int res = search_forward_error(trie, curr, prefix);

	    //If the entire prefix fit then return, else continue backwards
	    if (res != -1)
		return res;
	}

	//Push current nodes letter and jump back one node
	prefix.push(trie[prev].letter);
	prev = curr;
	curr = trie[curr].parent;
    }
    
    return -1;
}

void build_automaton(std::vector<Node>& trie)
{
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
	
//SCHAR_MAX = 127, if custom character demands higher values
	//then change to USCHAR_MAX
	for (char ch{0}; ch < SCHAR_MAX; ch++)
	{
	    //If the current character does not have a valid next edge
	    if (trie[curr].next.find(ch) == trie[curr].next.end())
	    {
		int res = search_backward_error(trie, curr, ch);

		//If search yilded a result then add the reset edge
		if (res != -1)
		{
		    trie[curr].reset.insert( {ch, res} );
		}
	    }
	}
    }
}

std::stringstream print_trie(std::vector<Node>& trie, int index = 0)
{
    std::stringstream stream{};


    
    for (auto it : trie[index].next)
    {
	stream << "->('"
	       << "this: "
	       << index
	       << " letter: '"
	       << trie[index].letter
	       << " parent: "
	       << trie[index].parent
	       << "' next: "
	       << it.second
	       << ") "
	       << print_trie(trie, it.second).str();
    }

    if (trie[index].next.size() == 0)
    {
	stream << "->('"
	       << "this: "
	       << index
	       << " letter: '"
	       << trie[index].letter
	       << " parent: "
	       << trie[index].parent
	       << ") ";
    }
    
    if (trie[index].word_done != -1)
    {
	stream << std::endl;
	return stream;
	}
    
	return stream;
}

int main()
{
    // std::string text;        
    // std::getline(std::cin, text);

    // std::vector<std::string> patterns{};
    // std::string tmp;
    // while (std::cin >> tmp)
    // 	patterns.push_back(tmp);

    // std::vector<Node> trie{ build_trie(patterns) };

    // std::cout << print_trie(trie).str() << std::endl;

    // return 0;

    std::string text = "abbabcabap";
    std::vector<std::string> patterns{"abbab", "abc", "bap"};

    std::vector<Node> trie = build_trie(patterns);

    std::cout << print_trie(trie).str() << std::endl;;
    
    build_automaton(trie);

    std::cout << print_trie(trie).str() << std::endl;;
    
    return 0;
}

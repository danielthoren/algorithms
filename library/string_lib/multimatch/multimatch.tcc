#include<map>
#include<algorithm>
#include<queue>
#include<limits>
#include<climits>
#include<stack>

#ifndef MULTIMATCH
#error 'multimatch.tcc' is not supposed to be included directly. Include 'multimatch.h' instead.
#endif

template<typename T>
template<typename IT>
struct  Multimatch<T>::insert_vec{
    using res_type = std::vector<std::vector<IT>>;

    insert_vec(IT initial_size = 0):
	result(initial_size)
	{};
    
    void insert(IT pattern, IT pos)
	{
	    result[pattern].push_back(pos);
	}

    res_type result;
};


template<typename T>
template<typename IT>
struct Multimatch<T>::insert_pair{
    using res_type = std::vector<std::pair<IT, IT>>;

    insert_pair(IT initial_size = 0):
	result{}
	{};    
    
    void insert(IT pattern, IT pos)
	{
	    result.push_back( {pattern, pos} );
	}

    res_type result;
};

template<typename T>
template<typename CONTAINER>
auto Multimatch<T>::string_multi_matching(T const& text)
    -> decltype( std::declval<CONTAINER>().insert(10, 10),
    	         typename CONTAINER::res_type{})
{
    CONTAINER matches(patterns.size());

    int curr = 0;

    for (unsigned long pos{0}; pos < text.size(); pos++)
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
		matches.insert(m, pos - patterns[m].size() + 1);
	    }
	}
    }
    return matches.result;
}

template<typename T>
std::vector<typename Multimatch<T>::Node> Multimatch<T>::build_trie(std::vector<T> const& patterns)
{
    std::vector<typename Multimatch<T>::Node> trie{ Node{{}, -1, 0, {}, -1} };
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

template<typename T>
int Multimatch<T>::search_backward_error(std::vector<typename Multimatch<T>::Node>& trie, int curr)
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


template<typename T>
void Multimatch<T>::build_automaton()
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

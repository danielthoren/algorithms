#include<vector>
#include<map>
#include<string>
#include<algorithm>
#include<iostream>
#include<sstream>

struct Node
{
    int word_done;
    char letter;
    std::map<char, int> next;
};

std::vector<Node> build_trie(std::vector<std::string>& patterns)
{    
    std::vector<Node> trie{ Node{-1, -1, {}} };
    int curr{0};
    
    for (unsigned p{0}; p < patterns.size(); p++)
    {
	for (unsigned l{0}; l < patterns[p].size(); l++)
	{
	    if (trie[curr].next.find(patterns[p][l]) == trie[curr].next.end())
	    {
		//Adding new node for letter l
		trie.push_back( Node{-1, patterns[p][l], {}} );

		//Creating vertex from current node to new node
		trie[curr].next[patterns[p][l]] = trie.size() - 1;
		//Stepping forward to the new node in the graph
		curr = trie.size() - 1;
	    }
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

std::stringstream print_trie(std::vector<Node>& trie, int index = 0)
{
    std::stringstream stream{};
    if (trie[index].word_done != -1)
    {
	stream << std::endl;
	return stream;
    }

    for (auto it : trie[index].next)
    {
	stream << "->('" << it.first << "' : " << it.second << ")" << print_trie(trie, it.second).str();
    }

    return stream;
}


int main()
{
    std::string text;        
    std::getline(std::cin, text);

    std::vector<std::string> patterns{};
    std::string tmp;
    while (std::cin >> tmp)
	patterns.push_back(tmp);

    std::vector<Node> trie{ build_trie(patterns) };

    std::cout << print_trie(trie).str() << std::endl;

    return 0;
}

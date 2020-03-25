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

#include "stringlib.h"

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

#include <iostream>
#include <string>
#include <vector>

#include "match.h"

int main()
{
    std::ios_base::sync_with_stdio(false);
    std::cin.tie(NULL);
    
    std::string pattern;
    std::string data;
    while (std::getline(std::cin, pattern))
    {
	std::getline(std::cin, data);

	dalg::Match match(pattern);
	
	std::vector<unsigned> matches{ match.match(data) };
	
	if (matches.size() > 0)
	    std::cout << matches[0];
	
	for (int n{1}; n < matches.size(); n++)
	    std::cout << " " << matches[n];
	std::cout << std::endl;
    }

    return 0;
}


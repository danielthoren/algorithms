#include <iostream>
#include <string>
#include <vector>

// std::vector<int> string_matching2(std::string& pattern, std::string& data)
// {
//     std::vector<int> prefix{ generate_prefix(pattern) };
//     std::vector<int> matches{};
    
//     int d_pos{0};
//     int p_pos{0};
//     while (d_pos <= (data.size() - pattern.size()))
//     {
// 	while (p_pos < (pattern.size()) && pattern[p_pos] == data[d_pos + p_pos])
// 	{
// 	    p_pos++;
// 	}
	
// 	if (p_pos == pattern.size())
// 	{
// 	    matches.push_back(d_pos);
// 	}

// 	p_pos--; //getting the index of the latest matched char
// 	if (p_pos >= 0)
// 	{
// 	    d_pos += (p_pos - prefix[p_pos]) + 1;
// 	    p_pos = prefix[p_pos];
// 	}
// 	else
// 	{
// 	    d_pos++;
// 	    p_pos = 0;
// 	}
//     }
//     return matches;
// }


std::vector<int> generate_prefix(std::string& pattern)
{
    std::vector<int> prefix{0};
    int i{0};
    for (int pos{1}; pos < pattern.size(); pos++)
    {
	while (i > 0 && pattern[i] != pattern[pos] && i < pattern.size())
	    i = prefix[i - 1];

	if (pattern[i] == pattern[pos])
	    i += 1;

	prefix.push_back(i);
    }
    return prefix;
}

std::vector<int> string_matching(std::string& pattern, std::string& data)
{
    std::vector<int> prefix{ generate_prefix(pattern) };
    std::vector<int> matches{};

    int p_off{0};
    int k{0};
    for (int j{0}; j < data.size(); j++)
    {
	if (pattern[k] == data[j])
	{
	    k++;
	    if (k == pattern.size())
	    {
		if (j - k + 1 == 511)
		    std::cout << " " << std::endl;
		
		matches.push_back(j - k + 1);
		k = prefix[k-1];
	    }
	}
	else
	{
	    if (k > 0)
	    	k = prefix[k - 1];
	    else
		k = prefix[0];
	    
	    if (k < 0)
	    {
		j++;
		k++;
	    }
	}
    }
    return matches;
}

int main()
{
    std::ios_base::sync_with_stdio(false);
    
    std::string pattern;
    std::string data;
    while (std::getline(std::cin, pattern))
    {
	std::getline(std::cin, data);
	
	std::vector<int> matches{ string_matching(pattern, data) };
	
	if (matches.size() > 0)
	    std::cout << matches[0];
	
	for (int n{1}; n < matches.size(); n++)
	    std::cout << " " << matches[n];
	std::cout << std::endl;
    }

    return 0;
}

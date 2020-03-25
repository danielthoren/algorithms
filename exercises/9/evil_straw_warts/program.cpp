#include <iostream>
#include <string>
#include <cmath>

using namespace std;

pair<int, string> get_palindrome(string word)
{
    int end{word.size() - 1};
    int start{0};
    int swaps{0};

    char unique{-1};
    
    for (int i{0}; i <= word.size(); i++)
    {
	//If in the middle and no letters were swapped then we have a
	//palindrome, otherwise reset
	if (end <= start)
	{	    
	    return {swaps, word};
	}
	
	//If the letters at equal distance from midpoint are not the
	//same and if the neighbouring letter is not the same then
	//swap
	if (word[end] != word[start])
	{
	    //find the same letter as start that is closest to end
	    int pos{end - 1};
	    while (word[pos] != word[start] && pos > start)
	    {
		pos--;
	    }

	    //Check if start letter is unique or not
	    if (pos > start)
	    {	    
		for (; pos < end; pos++)
		{
		    char tmp = word[pos];
		    word[pos] = word[pos + 1];
		    word[pos + 1] = tmp;
		
		    swaps++;
		}
	    }

	    //start letter is unique, push forward
	    if (word[start] != word[end])
	    {
	    	if (word.size() % 2 != 0 && (unique == word[start] || unique == -1))
	    	{
		    unique = word[start];
		    
		    char tmp = word[start + 1];
		    word[start + 1] = word[start];
		    word[start] = tmp;
		
		    swaps++;
		    
		    end++;
		    start--;
	    	}
		else
		{
		    return {-1, word};
		}
	    }
	}
	
	end--;
	start++;
    }
    return {-1, word};
}


int main()
{
    std::ios_base::sync_with_stdio(false);
    
    int n;
    cin >> n;

    for (int c{0}; c < n; c++)
    {
	string word;
	cin >> word;

	pair<int, string> res = get_palindrome(word);
	if (res.first != -1)
	{
	    cout << res.first << endl;
	}
	else
	{
	    cout << "Impossible" << endl;
	}
    }
}

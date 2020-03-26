#include <vector>
#include <cstdio>
#include <tuple>
#include <algorithm>

using namespace std;

bool get_manipulation(vector<pair<int, int>>& matches, vector<int> scores, vector<int>& res, int max_score)
{
    auto it = max_element(scores.begin(), scores.end() - 1);
    if (*it >= max_score)
    {
	return false;
    }
    
    if (matches.size() == 0)
    {
	return true;
    }    
    
    if (matches.size() == 0)
    {
	return true;
    }
   
    pair<int, int> match = matches[0];
    matches.erase(matches.begin(), matches.begin()+1);

    if (match.first == scores.size() - 1)
    {
	res.push_back(0);
	scores[scores.size() - 1] += 2;
	
	return get_manipulation(matches, scores, res, max_score);
    }
    else if (match.second == scores.size() - 1)
    {	
	res.push_back(2);
	scores[scores.size() - 1] += 2;
	
	return get_manipulation(matches, scores, res, max_score);
    }


    if (scores[match.first] > scores[match.second])
    {	
	res.push_back(2);
	scores[match.second] += 2;
	
	bool ret = get_manipulation(matches, scores, res, max_score);

	if (ret)
	{
	    return true;
	}

	//If letting first team win did not work, try a draw
	res.pop_back();
	res.push_back(1);
	scores[match.first] += 1;
	scores[match.second] -= 1;

	ret = get_manipulation(matches, scores, res, max_score);

	if (ret)
	{
	    return true;
	}

	//If draw does not work try letting second team win
	res.pop_back();
	res.push_back(0);
	scores[match.first] += 1;
	scores[match.second] -= 1;
	
	ret = get_manipulation(matches, scores, res, max_score);

	if (ret)
	{
	    return true;
	}

	res.pop_back();
	matches.push_back(match);
	return false;
    }

    else
    {	
	res.push_back(0);
	scores[match.first] += 2;

	bool ret = get_manipulation(matches, scores, res, max_score);

	if (ret)
	{
	    return true;
	}

	//If letting first team win did not work, try a draw
	res.pop_back();
	res.push_back(1);
	scores[match.first] -= 1;
	scores[match.second] += 1;

	ret = get_manipulation(matches, scores, res, max_score);

	if (ret)
	{
	    return true;
	}

	//If draw does not work try letting second team win
	res.pop_back();
	res.push_back(2);
	scores[match.first] -= 1;
	scores[match.second] += 1;

	ret = get_manipulation(matches, scores, res, max_score);

	if (ret)
	{
	    return true;
	}

	res.pop_back();
	matches.push_back(match);
	return false;
    }
    
    return false;
}


int main()
{
    long n, m;
    scanf(" %ld", &n);

    while (n != -1)
    {
	scanf(" %ld", &m);
	vector<int> scores{};
	scores.push_back(-1);
	for (int i{0}; i < n; i++)
	{
	    int score;
	    scanf(" %d", &score);
	    scores.push_back(score);
	}

	int max_score{scores[n]};
	vector<pair<int,int>>matches{};
	for (int p{0}; p < m; p++)
	{
	    int a, b;
	    scanf(" %d", &a);
	    scanf(" %d", &b);

	    if (a == n || b == n)
		max_score += 2;

	    matches.push_back({a, b});
	}

	vector<int> result{};
	bool res = get_manipulation(matches, scores, result, max_score);

	if (res)
	{
	    if (result.size() > 0)
		printf("%d", result[0]);
	    for (int i{1}; i < m; i++)
	    {
		printf(" %d", result[i]);
	    }
	    printf("\n");
	}
	else
	{
	    printf("NO\n");
	}
	
	scanf(" %ld", &n);
    }

    return 0;
}

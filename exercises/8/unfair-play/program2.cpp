#include <vector>
#include <cstdio>
#include <tuple>
#include <algorithm>

#include "max_flow.h"

using namespace std;

enum Match{
    FirstWon, SecondWon, Tie
};

struct Match_result
{    
    bool success{false};
    std::vector<Match> result{};
};

template<typename T>
void gen_result(Match_result& res, Max_flow<T, T> const& max_flow,
		std::vector<std::pair<T, T>> const& matches,
		T match_offset,
		T team_offset)
{
    std::vector<typename Max_flow<T,T>::Node> orig_graph = max_flow.get_orig_graph();

    for (T m{0}; m < matches.size(); m++)
    {
	if (matches[m].first == win_team)
	{
	    res.result.push_back(Match::FirstWon);
	}
	else if  (matches[m].second == win_team)
	{
	    res.result.push_back(Match::SecondWon);
	}
	else
	{
	    if(orig_graph[m + match_offset].edges[0].curr_flow == TIE_SCORE)
	    {
		res.result.push_back(Match::Tie);
	    }
	    else if (orig_graph[m + match_offset].edges[0].curr_flow == WIN_SCORE)
	    {
		if (orig_graph[m + match_offset].edges[0].end_node == matches[m].first)
		    res.result.push_back(Match::FirstWon);
		else
		    res.result.push_back(Match::SecondWon);
	    }
	    else
	    {
		if (orig_graph[m + match_offset].edges[1].end_node == matches[m].first)
		    res.result.push_back(Match::FirstWon);
		else
		    res.result.push_back(Match::SecondWon);
	    }
	}
    }
}

template<typename T>
Match_result baseball_elimination(std::vector<pair<T, T>>& matches, std::vector<T>& scores, T win_team)
{
    const int WIN_SCORE = 2;
    const int TIE_SCORE = 1;
    
    T size{scores.size() + matches.size() + 2};
    T sink{ size - 1 };
    
    Max_flow<T, T> max_flow(size, 0, sink);

    T match_offset{1};
    T team_offset{match_offset + matches.size()};

    //Connect all match nodes to source
    for (T m{0}; m < matches.size(); m++)
    {
	if (m != win_team)
	{
	    max_flow.connect(0, m + match_offset, WIN_SCORE);
	}
    }

    //The max remaining score that the win team can earn
    T win_r{0};
    
    //Connect match nodes to the two teams involved in said match
    for (T m{0}; m < matches.size(); m++)
    {
	if (matches[m].first == win_team || matches[m].second == win_team)
	{
	    win_r += WIN_SCORE;
	}
	else
	{
	    max_flow.connect(m + match_offset, matches[m].first, std::numeric_limits<T>::max());
	    max_flow.connect(m + match_offset, matches[m].second, std::numeric_limits<T>::max());
	}
    }

    T win_score{ win_r + scores[win_team] };

    //Connect all team nodes to drain
    for (T t{0}; t < scores.size(); t++)
    {
	if (t != win_team)
	{
	    //Max remaining wins that team t is allowed to win
	    T max_win_remain{ win_score - scores[t] };
	    max_flow.connect(sink, t + team_offset, max_win_remain);
	}
    }

    T flow = max_flow.calculate_max_flow();

    std::vector<typename Max_flow<T,T>::Node>& graph = max_flow.get_graph();
    Match_result res{};

    //Check if all edges from source to matches are saturated, if not
    //then win_team cannot win, if they are then win_team can win
    for (typename Max_flow<T,T>::Edge e : graph[0])
    {
	if (e.curr_flow != e.max_flow)
	{
	    return res;
	}
    }

    gen_result(res, max_flow, matches, match_offset, team_offset);
    
    return res;       
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

	vector<pair<int,int>>matches{};
	for (int p{0}; p < m; p++)
	{
	    int a, b;
	    scanf(" %d", &a);
	    scanf(" %d", &b);

	    matches.push_back({a, b});
	}

	vector<Match> result{};
	result = baseball_elimination(matches, scores, result);

	if (result.size() != 0)
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



template<typename T>
bool Baseball_elimination<T>::is_eliminated()
{        
    //Connect all match nodes to source
    for (T m{0}; m < matches.size(); m++)
    {
	if (matches[m].first != win_team && matches[m].second != win_team)
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
	    max_flow.connect(m + match_offset, matches[m].first + team_offset, std::numeric_limits<T>::max());
	    max_flow.connect(m + match_offset, matches[m].second + team_offset, std::numeric_limits<T>::max());
	}
    }

    T win_score{ win_r + start_scores[win_team] };
    if (win_score <= *std::max_element(start_scores.begin(), start_scores.end()))
	return true;

    //Connect all team nodes to drain
    for (T t{1}; t < start_scores.size(); t++)
    {
	if (t != win_team)
	{
	    //Max remaining wins that team t is allowed to win
	    T max_win_remain{ win_score - start_scores[t] - 1};
	    max_flow.connect(t + team_offset, sink, max_win_remain);
	}
    }

    T flow = max_flow.calculate_max_flow();

    std::vector<typename Max_flow<T,T>::Node>& graph = max_flow.get_graph();

    //Check if all edges from source to matches are saturated, if not
    //then win_team cannot win, if they are then win_team can win
    for (typename Max_flow<T,T>::Edge e : graph[0].edges)
    {
	if (e.curr_flow != e.max_flow)
	{
	    return true;
	}
    }

    gen_result();
    
    return false;
}

template<typename T>
void Baseball_elimination<T>::gen_result()
{
    std::vector<typename Max_flow<T,T>::Node> orig_graph = max_flow.get_orig_graph();

    for (T m{0}; m < matches.size(); m++)
    {
	if (matches[m].first == win_team)
	{
	    result.push_back(Match::FirstWon);
	}
	else if  (matches[m].second == win_team)
	{
	    result.push_back(Match::SecondWon);
	}
	else
	{
	    if(orig_graph[m + match_offset].edges[0].curr_flow == TIE_SCORE)
	    {
		result.push_back(Match::Tie);
	    }
	    else if (orig_graph[m + match_offset].edges[0].curr_flow == WIN_SCORE)
	    {
		if (orig_graph[m + match_offset].edges[0].end_node == matches[m].first + team_offset)
		    result.push_back(Match::FirstWon);
		else
		    result.push_back(Match::SecondWon);
	    }
	    else
	    {
		if (orig_graph[m + match_offset].edges[1].end_node == matches[m].first + team_offset)
		    result.push_back(Match::FirstWon);
		else
		    result.push_back(Baseball_elimination<T>::Match::SecondWon);
	    }
	}
    }
}

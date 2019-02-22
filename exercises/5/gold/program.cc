#include <vector>
#include <algorithm>
#include <iostream>

using namespace std;

int breadth_first(vector<vector<pair<char, bool>>>& map, pair<int,int> p_pos)
{

    map[p_pos.first][p_pos.second].second = true;

    if (map[p_pos.first][p_pos.second + 1].first == 'T' ||
	map[p_pos.first][p_pos.second - 1].first == 'T' ||
	map[p_pos.first + 1][p_pos.second].first == 'T' ||
	map[p_pos.first - 1][p_pos.second].first == 'T')
    {
	if (map[p_pos.first][p_pos.second].first == 'G')
	    return 1;
	else
	    return 0;
    }   

    int gold{0};
    pair<char, bool>* pos = &map[p_pos.first][p_pos.second + 1];
    if (!pos->second && pos->first != '#')
	gold += breadth_first(map, {p_pos.first, p_pos.second + 1});

    pos = &map[p_pos.first][p_pos.second - 1];
    if (!pos->second && pos->first != '#')
	gold += breadth_first(map, {p_pos.first, p_pos.second - 1});

    pos = &map[p_pos.first + 1][p_pos.second];
    if (!pos->second && pos->first != '#')
	gold += breadth_first(map, {p_pos.first + 1, p_pos.second});

    pos = &map[p_pos.first - 1][p_pos.second];
    if (!pos->second && pos->first != '#')
	gold += breadth_first(map, {p_pos.first - 1, p_pos.second});

    if (map[p_pos.first][p_pos.second].first == 'G')
	gold++;

    return gold;
}

int main()
{
    int width, height;
    cin >> width;
    cin >> height;

    pair<int,int> p_pos;
    
    vector<vector<pair<char, bool>>> map{};
    for (int h{0}; h < height; h++)
    {
	map.push_back({});
	for (int w{0}; w < width; w++)
	{
	    char in;
	    cin >> in;
	    map.at(h).push_back({in, false});
	    if (in == 'P')
	    {
		p_pos.first = h;
		p_pos.second = w;
	    }
	}
    }

    // for (int h{0}; h < height; h++)
    // {
    // 	for (int w{0}; w < width; w++)
    // 	{
    // 	    cout << map[h][w].first;
    // 	}
    // 	cout << endl;
    // }

    // cout << endl << p_pos.first << ", " << p_pos.second << endl;

    cout << breadth_first(map, p_pos) << endl;
}

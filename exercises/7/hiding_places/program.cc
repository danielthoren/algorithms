#include <iostream>
#include <algorithm>
#include <vector>
#include <limits.h>
#include <map>
#include <string>

using namespace std;

struct Edge
{
    int end_node;
    int cost;
};

struct Node
{
    int min_cost;
    bool visited;
    int parent;
    vector<Edge> edges;
};

void update_distance(vector<Node>& graph, Node& node)
{
    if (node.min_cost != INT_MAX)
    {
	for (Edge edge: node.edges)
	{
	    int tmp = node.min_cost + edge.cost;
	    if (tmp < graph.at(edge.end_node).min_cost &&
		!graph.at(edge.end_node).visited)
	    {
		graph.at(edge.end_node).min_cost = tmp;
	    }
	}
	node.visited = true;
    }
}

/*
 *Takes a graph as a vector where the index is the node number and each 
 *node is of type "Node" which contains edges, cost and if its visited or not
 */
vector<Node> dijkstras(vector<Node> graph, int start_node)
{
    graph.at(start_node).min_cost = 0;
    int prev_node = start_node;
    for (int i{0}; i < graph.size(); i++)
    {
        int min_node = -1;
	for (int n{0}; n < graph.size(); n++)
	{
	    if (!graph.at(n).visited)
	    {
		if (min_node == -1 || graph.at(n).min_cost < graph.at(min_node).min_cost)
		{
		    min_node = n;
		}
	    }
	}
	graph.at(min_node).parent = prev_node;
	prev_node = min_node;
	update_distance(graph, graph.at(min_node));
    }
    return graph;
}

/*
 *returns shortest path, assumes there is a shortest path
 */
vector<int> get_shortest_path(vector<Node>& graph, int start, int end)
{
    vector<int> path{};
    int curr = end;
    while (curr != start)
    {
	path.insert(path.begin(), curr);
	curr = graph.at(curr).parent;
    }
    path.insert(path.begin(), start);
    return path;
}

pair<int, vector<string>> get_longest_paths(vector<Node>& graph, int start)
{
    const map<int, char> column{
	{0, 'a'},
	{1, 'b'},
	{2, 'c'},
	{3, 'd'},
	{4, 'e'},
	{5, 'f'},
	{6, 'g'},
	{7, 'h'}
    };
    
    vector<string> paths{};
    int distance{0};

    for (Node n : graph)
	if (n.min_cost > distance)
	    distance = n.min_cost;

    for (int vert_p{0}; vert_p < 8; vert_p++)
    {
	for (int hori_p{0}; hori_p < 8; hori_p++)
	{
	    int pos = vert_p * 8 + hori_p;
	    if (graph.at(pos).min_cost == distance)
	    {
		paths.push_back(string({column.at(hori_p),
				static_cast<char>('0' + vert_p + 1)}));
		vector<int> path = get_shortest_path(graph, start, pos);
		cout << paths.at(paths.size() - 1) << " : ";
		for (int n : path)
		    cout << n << " -> ";
		cout << endl;
	    }
	}
    }

    return {distance, paths};
}

int main()
{
    vector<Node> board{};

    for (int vert_p{0}; vert_p < 8; vert_p++)
    {
	for (int hori_p{0}; hori_p < 8; hori_p++)
	{
	    Node node;
	    node.min_cost = INT_MAX;
	    node.visited = false;

	    int v_tmp;
	    int pos_tmp;

	    if (vert_p < 6)
	    {
		v_tmp = (vert_p * 8) + 2 * 8; //curr row + 2 rows (up)
		pos_tmp = v_tmp + hori_p;     //curr pos

		if (hori_p < 7)
		    node.edges.push_back(Edge{pos_tmp + 1, 1});
		if (hori_p > 0)
		    node.edges.push_back(Edge{pos_tmp - 1, 1});
	    }

	    if (vert_p > 1)
	    {
		v_tmp = (vert_p * 8) - 2 * 8;     //curr row - 2 rows (down)
		pos_tmp = v_tmp + hori_p;         //curr pos

		if (hori_p < 7)
		    node.edges.push_back(Edge{pos_tmp + 1, 1});
		if (hori_p > 1)
		    node.edges.push_back(Edge{pos_tmp - 1, 1});
	    }

	    if (hori_p > 1)
	    {
		v_tmp = (vert_p * 8);
		pos_tmp = v_tmp + hori_p - 2;     //curr pos - 2 columns (left)

		if (vert_p < 7)
		    node.edges.push_back(Edge{pos_tmp + 8, 1});//one row up
		if (vert_p > 0)
		    node.edges.push_back(Edge{pos_tmp - 8, 1});//one row down
	    }

	    if (hori_p < 6)
	    {
		v_tmp = (vert_p * 8);
		pos_tmp = v_tmp + hori_p + 2;     //curr pos + 2 columns (right)

		if (vert_p < 7)
		    node.edges.push_back(Edge{pos_tmp + 8, 1});//one row up
		if (vert_p > 0)
		    node.edges.push_back(Edge{pos_tmp - 8, 1});//one row down
	    }

	    board.push_back(node);
	}
    }

    const map<char, int> column{
	{'a', 0},
	{'b', 1},
	{'c', 2},
	{'d', 3},
	{'e', 4},
	{'f', 5},
	{'g', 6},
	{'h', 7}
    };
    
    int cases;
    cin >> cases;

    for (int c{0}; c < cases; c++)
    {
	string in_data;
	cin >> in_data;
    	int start_pos = column.at(in_data[0]) + (in_data[1] - '0' - 1) * 8;

	vector<Node> result = dijkstras(board, start_pos);

	pair<int, vector<string>> output = get_longest_paths(result, start_pos);
	sort(output.second.begin(), output.second.end(), [] (string& s1, string&s2)
	     {
		 if (s1[1] != s2[1])
		     return (s1[1] - '0') > (s2[1] - '0');
		 return s1[0] < s2[0];
	     });

	cout << output.first << " ";
	for (string n : output.second)
	{
	    cout << n << " ";
	}

	cout << endl;
    }

    return 0;
}

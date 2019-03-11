#include <iostream>
#include <algorithm>
#include <vector>
#include <limits.h>

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

void update_distance(vector<Node>& graph, Node& node, int node_index)
{
    if (node.min_cost != INT_MAX)
    {
	for (Edge& edge: node.edges)
	{
	    int tmp = node.min_cost + edge.cost;
	    if (tmp < graph.at(edge.end_node).min_cost &&
		!graph.at(edge.end_node).visited)
	    {
		graph.at(edge.end_node).min_cost = tmp;

		//Uncomment to enable backtracking of path
		//graph.at(edge.end_node).parent = node_index;
	    }
	}
	node.visited = true;
    }
}

/*
 *Takes a graph as a vector where the index is the node number and each 
 *node is of type "Node" which contains edges, cost and if its visited or not
 */
void dijkstras(vector<Node>& graph, int start_node)
{
    graph.at(start_node).min_cost = 0;
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
	update_distance(graph, graph.at(min_node), min_node);
    }
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

int main()
{
    std::ios_base::sync_with_stdio(false);
    
    int node_count, edge_count, querie_count, start_node;
    cin >> node_count >> edge_count >> querie_count >> start_node;

    while (true)
    {
	vector<Node> graph(node_count); // {min_cost_of_node, edges}

	for (Node& node : graph)
	{
	    node.min_cost = INT_MAX;
	    node.visited = false;
	}
    
	for (int edge{0}; edge < edge_count; edge++)
	{
	    int n1, n2, cost;
	    cin >> n1 >> n2 >> cost;
	    Edge e{n2, cost};
	    graph.at(n1).edges.push_back(e);	
	}

	dijkstras(graph, start_node);

	for (int i{0}; i < querie_count; i++)
	{
	    int querie;
	    cin >> querie;

	    if (graph.at(querie).min_cost == INT_MAX)
		cout << "Impossible" << endl;
	    else
		cout << graph.at(querie).min_cost << endl;
	}
	cin >> node_count >> edge_count >> querie_count >> start_node;
		
	if (node_count == 0 && edge_count == 0 && querie_count == 0 && start_node == 0)
	    break;

	cout << endl;
    }

    return 0;
    
}

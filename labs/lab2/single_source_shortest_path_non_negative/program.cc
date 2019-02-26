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

void dijkstras(vector<Node>& graph, int start_node)
{
    graph.at(start_node).min_cost = 0;
    for (int i{0}; i < graph.size(); i++)
    {
	Node* min_node = nullptr;
	for (Node& n : graph)
	{
	    if (!n.visited)
	    {
		if (min_node == nullptr || n.min_cost < min_node->min_cost)
		{
		    min_node = &n;
		}
	    }
	}
       
	update_distance(graph, *min_node);
    }
}

int main()
{
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

#include <iostream>
#include <algorithm>
#include <vector>
#include <limits.h>

using namespace std;

struct Edge
{
    int end_node;
    int blocked;  //When edge starts to be blocked, -1 if never blocked
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

	    //Adding time until edge available to cost
	    if (edge.blocked != -1 &&
		node.min_cost >= edge.blocked &&
		node.min_cost <= (edge.blocked + edge.cost))
	    {
		tmp += (edge.blocked + edge.cost) - node.min_cost;
	    }
	    
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
void dijkstras(vector<Node>& graph, int start_node, int start_time)
{
    graph.at(start_node).min_cost = start_time;
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

Edge& get_edge(vector<Edge>& edges, int end_node)
{
    for (Edge& e : edges)
    {
	if (e.end_node == end_node)
	    return e;
    }
}

int main()
{
    int node_count, edge_count;
    cin >> node_count >> edge_count;

    vector<Node> graph(node_count);
    for_each(graph.begin(), graph.end(), [] (Node& n) {n.min_cost = INT_MAX;});
    
    int luka_start, luka_goal, time_diff, george_node_count;
    cin >> luka_start >> luka_goal >> time_diff >> george_node_count;
    luka_start--;
    luka_goal--;

    vector<int> george_traverse{};
    for (int i{0}; i < george_node_count; i++)
    {
	int n;
	cin >> n;
	george_traverse.push_back(--n);
    }

    for (int i{0}; i < edge_count; i++)
    {
	int n1, n2, cost;	
	cin >> n1 >> n2 >> cost;
	n1--;
	n2--;

	Edge edge1{n2, -1, cost};
	Edge edge2{n1, -1, cost};

	graph.at(n1).edges.push_back(edge1);
	graph.at(n2).edges.push_back(edge2);
    }

    int george_time{0};
    for (int g{0}; g < george_traverse.size() - 1; g++)
    {
	
	Node& n1 = graph.at(george_traverse.at(g));       
	Edge& edge1 = get_edge(n1.edges, george_traverse.at(g + 1));

	Node& n2 = graph.at(george_traverse.at(g + 1));
	Edge& edge2 = get_edge(n2.edges, george_traverse.at(g));

	edge1.blocked = george_time;
	edge2.blocked = george_time;
	george_time += edge1.cost;
    }

    dijkstras(graph, luka_start, time_diff);

    cout << graph.at(luka_goal).min_cost - time_diff << endl;
}

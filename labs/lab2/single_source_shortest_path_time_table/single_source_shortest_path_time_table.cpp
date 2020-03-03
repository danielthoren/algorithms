#include <algorithm>
#include <vector>
#include <limits.h>
#include <functional>

using namespace std;

/**
 * Author: Daniel Thorén
 *
 * Class that solves the shortest path problem with time tables. This
 * means that each edge can be traversed at times t0 + t*p for all
 * nonnegative integers.
 */
class Shortest_path_time_table
{
private:
    struct Edge;
    struct Node;
    
public:

    /**
     * Initializes the graph to the given size
     *
     * size: The size of the graph
     */
    Shortest_path_time_table(int size) : graph(size)
	{}

    /**
     * Resets the graphs state but not its connections
     */
    void resetGraph()
	{
	    for (int i{0}; i < graph.size(); i++)
	    {
		graph.at(i).min_cost = INT_MAX;
		graph.at(i).visited = false;
	    }
	}

    /**
     * Connects two nodes, node 1 and 2 with a one way edge with a given cost.
     * The connection is available at times t0 + t*p
     *
     * Time complexity: O(1)
     *
     * n1  : The node the edge leads from
     * N2  : The node the edge leads to
     * cost: The cost of traversing the edge
     * t0  : The first time the connection is available
     * p   : The interval at which the connection is available
     */
    void connect(int n1, int n2, int cost, int t0, int p)
	{
	    if (n1 < graph.size() && n2 < graph.size())
	    {
		Edge e{n2, cost, t0, p};
		graph.at(n1).edges.push_back(e);
	    }
	    else
	    {
		throw std::out_of_range("Tried to add connection between nonesitant nodes");
	    }
	}

    /*
     * Returns the shortest path betwee the set start node and the
     * given end node. If there is no path between them it returns an
     * empty vector.
     *
     * Time complexity: O(n)
     *
     * end: The node to find path to
     */
    vector<int> get_shortest_path(int end)
	{
	    vector<int> path{};
	    int curr = end;
	    int i{0};
	    for (; curr != start && i < graph.size(); i++)
	    {
		path.insert(path.begin(), curr);
		curr = graph.at(curr).parent;
	    }
	    if (i == graph.size())
	    {		
		return vector<int>();
	    }
	    
	    path.insert(path.begin(), start);
	    return path;
	}

    /**
     * Returns the shortest distance between the set start node and
     * the given end node. Returns INT_MAX if there is no path
     *
     * Time complexity: O(1)
     *
     * end: The node to measure the distance to
     */
    int get_shortest_distance(int end)
	{
	    return graph.at(end).min_cost;
	}
    

    /*
     * Searches the graph for the shortest path between start node and
     * every other node. After this method has been called the method
     * get_shortest_distance and get_shortest_path can be used to
     * query the graph
     *
     * Time complexity: O(n^2) (n = amount of nodes)
     *
     * start_node: The node from which to search
     */
    void dijkstras(int start_node)
	{
	    resetGraph();
	    start = start_node;
	    
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
		update_distance(graph.at(min_node));
	    }
	}

private:
    
    struct Edge
    {
	int end_node;
	int cost;
	int t0;
	int p;
    };

    struct Node
    {
	int min_cost;
	bool visited;
	int parent;
	vector<Edge> edges;
    };

    /**
     * If the following conditions are true for a neighbour node then
     * the cost of that node is updated:
     * -> The edge is available
     * -> The cost of the current node + the edge cost < neighbour nodes min_cost
     * -> The neighbour node has not been visited
     *
     * It also checks if it is worth waiting until an edge is available
     *
     * Time complexity: O(e) (worst case this node contains all edges)
     *
     * node_index: The index of the current node
     */
    void update_distance(Node& node)
	{
	    if (node.min_cost != INT_MAX)
	    {
		for (Edge edge: node.edges)
		{
		    int tmp = node.min_cost + edge.cost;

		    //Adding time until edge available to cost
		    if (edge.p == 0 && node.min_cost > edge.t0)
		    {
			tmp = INT_MAX;	    
		    }
		    else if (node.min_cost < edge.t0)
		    {
			tmp += edge.t0 - node.min_cost;
		    }
		    else if (edge.p != 0 && (node.min_cost - edge.t0) % edge.p != 0)
		    {
			tmp += edge.p - ((node.min_cost - edge.t0) % edge.p);
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

    std::vector<Node> graph{};
    int start;
};

int main()
{
    int node_count, edge_count, querie_count, start_node;

    scanf(" %d", &node_count);
    scanf(" %d", &edge_count);
    scanf(" %d", &querie_count);
    scanf(" %d", &start_node);

    while (true)
    {
	Shortest_path_time_table graph(node_count);
    
	for (int edge{0}; edge < edge_count; edge++)
	{
	    int n1, n2, t0, p, cost;
	    scanf(" %d", &n1);
	    scanf(" %d", &n2);
	    scanf(" %d", &t0);
	    scanf(" %d", &p);
	    scanf(" %d", &cost);

	    graph.connect(n1, n2, cost, t0, p);
	}

	graph.dijkstras(start_node);

	for (int i{0}; i < querie_count; i++)
	    {
		int querie;
		scanf(" %d", &querie);

		int shortest = graph.get_shortest_distance(querie);
		if (shortest == INT_MAX)
		    printf("Impossible\n");
		else
		    printf("%d\n", shortest);
	    }
	scanf(" %d", &node_count);
	scanf(" %d", &edge_count);
	scanf(" %d", &querie_count);
	scanf(" %d", &start_node);
		
	if (node_count == 0 && edge_count == 0 && querie_count == 0 && start_node == 0)
		break;

	printf("\n");
    }

    return 0;
    
    }

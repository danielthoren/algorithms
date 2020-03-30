#include <algorithm>
#include <vector>
#include <queue>
#include <functional>
#include <limits.h>

using namespace std;

/**
 * Author: Daniel Thorén
 *
 * Class that solves the shortest path problem with non negative
 * weights. Contains a number of methods to query the graphx
 */
class Shortest_path_non_negative
{
private:
    struct Edge;
    struct Node;
public:

    /**
     * Initializes the size of the graph
     *
     * size: The size of the graph
     */
    Shortest_path_non_negative(int size) : graph(size)
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
		graph.at(i).index = i;
	    }
	}

    /**
     * Connects two nodes, node 1 and 2 with a one way edge with a given cost
     *
     * Time complexity: O(1)
     *
     * n1  : The node the edge leads from
     * N2  : The node the edge leads to
     * cost: The cost of traversing the edge
     */
    void connect(int n1, int n2, int cost)
	{
	    if (n1 < graph.size() && n2 < graph.size())
	    {
		Edge e{n2, cost};
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
     * Time complexity: O(e + n * log n) (n = amount of nodes)
     *
     * start_node: The node from which to search
     */
    void dijkstras(int start_node)
	{
	    resetGraph();

	    graph.at(start_node).min_cost = 0;

	    //Slow solution since it stores copies in the priority
	    //queue. Does not compile with references and gets wrong
	    //awnswer with pointers
	    std::priority_queue<Node, std::vector<Node>, Queue_comparator> min_queue{};
	    min_queue.push(graph.at(start_node));

	    while (!min_queue.empty())
	    {
		int min_node = min_queue.top().index;
		min_queue.pop();

		if (! graph.at(min_node).visited)
		{
		    update_distance(min_node, min_queue);
		}
	    }
	}

private:
    struct Edge
    {
	int end_node;
	int cost;
    };

    struct Node
    {
	int index;
	int min_cost;
	bool visited;
	int parent;
	vector<Edge> edges;
    };

    /**
     * Comparator used in min queue
     */
    class Queue_comparator
    {
    public:
	bool operator() (Node n1, Node n2)
	    {
		return n1.min_cost > n2.min_cost;
	    }
    };



    /**
     * If the following conditions are true for a neighbour node then
     * the cost of that node is updated:
     * -> The cost of the current node + the edge cost < neighbour nodes min_cost
     * -> The neighbour node has not been visited
     *
     * Time complexity: O(e) (worst case this node contains all edges)
     *
     * node_index: The index of the current node
     */
    void update_distance(int node_index,
			 std::priority_queue<Node, std::vector<Node>, Queue_comparator>& min_queue)
	{
	    Node& node = graph.at(node_index);
	    if (node.min_cost != INT_MAX)
	    {
		for (Edge& edge: node.edges)
		{
		    int tmp = node.min_cost + edge.cost;
		    if (tmp < graph.at(edge.end_node).min_cost &&
			!graph.at(edge.end_node).visited)
		    {
			graph.at(edge.end_node).min_cost = tmp;

			min_queue.push(graph.at(edge.end_node));
                        //Enable backtracking of path
			graph.at(edge.end_node).parent = node_index;
		    }
		}
		node.visited = true;
	    }
	}

    vector<Node> graph{};
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
	Shortest_path_non_negative graph(node_count);
    
	for (int edge{0}; edge < edge_count; edge++)
	{
	    int n1, n2, cost;
	    scanf(" %d", &n1);
	    scanf(" %d", &n2);
	    scanf(" %d", &cost);
	    
	    graph.connect(n1, n2, cost);
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

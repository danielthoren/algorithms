#include <algorithm>
#include <vector>
#include <queue>
#include <functional>
#include <limits.h>
#include <cmath>
#include <iostream>

using namespace std;

using T = long long;

    struct Edge
    {
	int end_node;
	double cost;
	bool subway{false};
    };

    struct Node
    {
	int index;
	double min_cost;
	bool visited;
	int parent;
	vector<Edge> edges;
	T x;
	T y;
    };

/**
 * Author: Daniel Thorén
 *
 * Class that solves the shortest path problem with non negative
 * weights. Contains a number of methods to query the graphx
 */
class Shortest_path_non_negative
{
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
		graph.at(i).min_cost = numeric_limits<double>::max();
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
    void connect(int n1, int n2, double cost, bool subway = false)
	{
	    if (n1 < graph.size() && n2 < graph.size())
	    {
		Edge e{n2, cost, subway};
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
    double get_shortest_distance(int end)
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

    vector<Node>& get_graph()
	{
	    return graph;
	}
    
private:


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
	    if (node.min_cost != numeric_limits<double>::max())
	    {
		for (Edge& edge: node.edges)
		{
		    double tmp = node.min_cost + edge.cost;
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

T distance(Node& n1, Node& n2)
{
    return pow(pow(n1.x - n2.x, 2) + pow(n1.y - n2.y, 2), 0.5);
}

int main()
{
    std::ios::sync_with_stdio(false);
    
    string scanf_str{" %d"};       

    T x;
    T y;
    
    Shortest_path_non_negative graph_obj(0);
    graph_obj.resetGraph();
    vector<Node>& graph = graph_obj.get_graph();

    cin >> x;
    cin >> y;

    Node n{};
    n.index = 0;
    n.min_cost = numeric_limits<double>::max();
    n.visited = false;
    n.x = x;
    n.y = y;
    graph.push_back(n);

    cin >> x;
    cin >> y;    

    n.index = 1;
    n.min_cost = numeric_limits<double>::max();
    n.visited = false;
    n.x = x;
    n.y = y;

    graph.push_back(n);

    double subway_speed = (40.0 / 60.0) * 1000.0; // metres/min
    double walk_speed = (10.0 / 60.0) * 1000.0; // metres/min

    int prev{-1};
    while(cin >> x)
    {
	cin >> y;

	if (x == -1)
	{
	    prev = -1;
	    continue;
	}
	T curr = graph.size();
	n.index = curr;
	n.min_cost = numeric_limits<double>::max();
	n.visited = false;
	n.x = x;
	n.y = y;
	    
	graph.push_back(n);       

	if (prev != -1)
	{
	    double dist = distance(graph[curr], graph[prev]);
	    double cost = dist / subway_speed;

	    //Connect both ways
	    graph_obj.connect(curr, prev, cost, true);
	    graph_obj.connect(prev, curr, cost, true);	    
	}
	prev = curr;
    }   

    for (T n{0}; n < graph.size(); n++)
    {
	for (T other{n + 1}; other < graph.size(); other++)
	{
	    double dist = distance(graph[n], graph[other]);
	    double cost = dist / walk_speed;

	    //Connect both ways
	    graph_obj.connect(n, other, cost, false);
	    graph_obj.connect(other, n, cost, false);
	}
    }

    graph_obj.dijkstras(0);
    double distance = graph_obj.get_shortest_distance(1);

    T min = round(distance);

    cout << min;
    
}

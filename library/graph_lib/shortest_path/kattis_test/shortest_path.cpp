#include <algorithm>
#include <vector>
#include <queue>
#include <functional>
#include <limits.h>

#include "shortest_path_non_negative.h"

using namespace std;


int main()
{
    int node_count, edge_count, querie_count, start_node;
    
    scanf(" %d", &node_count);
    scanf(" %d", &edge_count);
    scanf(" %d", &querie_count);
    scanf(" %d", &start_node);

    while (true)
    {
	Shortest_path_non_negative<int> graph(node_count);
    
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

#include <iostream>

#include "point.h"
#include "line.h"

using namespace std;

line<int> read_line()
{
    int x1, y1, x2, y2;
    cin >> x1 >> y1 >> x2 >> y2;
    line<int> l1{x1, y1, x2, y2};

    return l1;
}

int main()
{
    std::ios_base::sync_with_stdio(false);
    int cases{};
    cin >> cases;

    for (int i{0}; i < cases; i++)
    {	
	line<int> l1 = read_line();
	line<int> l2 = read_line();

	
    }
    
}

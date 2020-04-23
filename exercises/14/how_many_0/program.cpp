#include <limits>
#include <cstdio>
#include <sstream>
#include <string>

using namespace std;

// int main()
// {
//     while (true)
//     {
//     	long from, to;
//     	scanf(" %ld", &from);
//     	scanf(" %ld", &to);

//     	if (from == -1 && to == -1)
//     	    break;

//     	long diff = to - from;
// 	long count{0};
	
//     	long curr = 10;
//     	while (true)
//     	{
//     	    long left_of = diff / curr;
// 	    if (left_of == 0)
// 		break;
	    
// 	    count += left_of * (curr / 10);
// 	    curr *= 10;
//     	}
// 	printf("%ld\n", count);
//     }
// }

int main()
{
    while (true)
    {
    	long from, to;
    	scanf(" %ld", &from);
    	scanf(" %ld", &to);

    	if (from == -1 && to == -1)
    	    break;

    	long diff = to - from;
	long count{0};
	
    	long curr = 10;

	stringstream stream{};
	diff >> stream;
	string number;
	stream >> number;
	
    	while (true)
    	{
    	    long left_of = diff / curr;
	    if (left_of == 0)
		break;
	    
	    count += left_of * (curr / 10);
	    curr *= 10;
    	}
	printf("%ld\n", count);
    }
}

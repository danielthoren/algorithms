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

long count_zeroes(long indata)
{
    stringstream stream{};
    stream << indata;
    string number;
    stream >> number;

    long g{0};
    long count{0};
    long curr_number{0};
    for (int c{0}; c < number.size(); c++)
    {
	long y = number[c] - '0';

	count = 10 * count + curr_number - g * (9 - y);
	curr_number = curr_number * 10 + y;

	if (y == 0)
	{
	    ++g;
	}
	    
    }
    return count;
}

int main()
{
    while (true)
    {
    	long from, to;
    	scanf(" %ld", &from);
    	scanf(" %ld", &to);

    	if (from == -1 && to == -1)
    	    break; 

	long to_count = count_zeroes(to);
	long from_count = count_zeroes(from);

	long res = to_count - from_count;


	stringstream stream2{};
	stream2 << from;
	string low;
	stream2 >> low;

	long start_zero{0};
	for (char c : low)
	{
	    if (c == '0')
		++start_zero;
	}
	res += start_zero;
	
	printf("%ld\n", res);
    }
}

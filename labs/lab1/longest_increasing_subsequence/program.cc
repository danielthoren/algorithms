
#include <iostream>
#include <numeric>
#include <vector>

void clone(int from[], int to[])
{
    for (int i = 0; i < from[0]; i++)
    {
	to[i] = from[i];
    }
}

template<int A, int B>
int largest_smaller(int seqences[A][B], int num)
{
    int largest = seqences[0][1];
    int largest_index = 0;
    for (int i = 0; i < A; i++)
    {
	if (largest < seqences[i][ seqences[i][0] ])
	{
	    largest = seqences[i][ seqences[i][0] ];
	    largest_index = i;
	}
    }
    return largest_index;
}

int get_index(int a, int b, int width)
{
    return a + b * width;
}

std::vector<int> longest_increasing_subsequence(std::vector<int>& input)
{
    //All possible sequences. First elem in each internal list is current size
    //of list:     [ [3, x, x, x] [2, x, x] ... ]
    int* sequences = new int[input.size() * (input.size() + 1)];
    int width = input.size();
    sequences[0] = 1;
    sequences[ get_index(0, 1, width) ] = input[0];

    for (int i = 1; i < input.size(); i++)
    {
	sequences[ get_index(i, 0, width) ] = -1;
    }

    //Current index in sequence arr
    int curr_index = 0;

    //Smallest end candidate
    int smallest = input[0];

    //Largest end candidate
    int largest = input[0];
    int largest_index = 0;
    
    for (int i = 0; i < input.size(); i++)
    {
	if (input[i] < smallest)
	{
	    smallest = input[i];
	    sequences[ get_index(++curr_index, 0, width) ] = 1;
	    sequences[++curr_index][1 get_index(] = input[i];
				    }
	else if (largest < input[i])
	{
	    largest = input[i];
	    clone(sequences[largest_index], sequences[++curr_index]);

	    int arr_size = ++sequences[curr_index][0];
	    sequences[curr_index][arr_size] = input[i];
	}
	else
	{
	    int index = largest_smaller(sequences, curr_index, input[i]);
	}
    }
}

int main()
{
    std::ios_base::sync_with_stdio(false);

    int length;

    std::cin >> length;
    
    std::vector<int> input;

    for (int i = 0; i < length; i++)
    {
	std::cin >> input[i];
    }

    std::vector<int> result = longest_increasing_subsequence(input);

    for (int i = 0; i < result.size(); i++)
    {
	std::cout << result[i] << " ";
    }
    std::cout << std::endl;
}

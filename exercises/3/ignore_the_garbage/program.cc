
#include <iostream>
#include <vector>
#include <map>

using namespace std;

int main()
{
    const map<int, int> numbers
    {
	{0,0},
	{1,1},
	{2,2},
	{3,5},
	{4,9},
	{5,8},
	{6,6}
    };
    int num;
    while (cin >> num)
    {
	while (num > 0)
	{
	    cout << numbers.find(num % 7)->second;
	    num /= 7;		
	}
	cout << endl;
    }

    return 0;
}

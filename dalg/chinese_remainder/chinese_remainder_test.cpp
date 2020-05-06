#include<iostream>
#include<utility>

#include "chinese_remainder.h"

using namespace std;

#define T long long

void test_merge_strong()
{
    std::vector<std::pair<T, T>> eq;
    eq.push_back( {2, 3} );
    eq.push_back( {3, 5} );

    std::pair<T, T> res = dalg::merge_mod_eq_strong(eq);
    if (res.first != 8)
	cout << "Failed 'test_merge_strong' test 1 got " << res.first << " expected 8" << endl;

    eq.clear();
    eq.push_back( {3, 4} );
    eq.push_back( {4, 7} );
    eq.push_back( {1, 9} );
    eq.push_back( {0, 11} );

    res = dalg::merge_mod_eq_strong(eq);
    if (res.first != 1243)
	cout << "Failed 'test_merge_strong' test 2 got " << res.first << " expected 1243" << endl;	
}

void test_merge_crt_strong()
{
    std::pair<T,T> res = dalg::merge_crt_strong<T>(10000,23000,9000,23000);
    if (res.first != 0 || res.second != 0)
    {
	cout << "Failed 'test_merge_crt_strong' test 1 got " <<
	    res.first <<
	    ", " <<
	    res.second <<
	    " expected 0, 0" <<
	    endl;
    }

    res = dalg::merge_crt_strong<T>(10000 ,23000 ,10000 ,23000);
    if (res.first != 10000 || res.second != 23000)
    {
	cout << "Failed 'test_merge_crt_strong' test 2 got " <<
	    res.first <<
	    ", " <<
	    res.second <<
	    " expected 10000 ,23000" <<
	    endl;
    }

    res = dalg::merge_crt_strong<T>(1234 ,2000 ,746 ,2002);
    if (res.first != 489234 || res.second != 2002000)
    {
	cout << "Failed 'test_merge_crt_strong' test 3 got " <<
	    res.first <<
	    ", " <<
	    res.second <<
	    " expected 489234 ,2002000" <<
	    endl;
    }
}

int main()
{
    test_merge_strong();
}

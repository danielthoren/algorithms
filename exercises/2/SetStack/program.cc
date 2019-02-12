#include <stack>
#include <iostream>
#include <algorithm>
#include <set>
#include <map>

using namespace std;

int push(stack<set<int>>& st)
{
    st.push({});
    return 0;
}

int dup(stack<set<int>>& st)
{
    set<int> tmp{st.top()};
    st.push(tmp);
    return tmp.size();
}

int intersect(stack<set<int>>& st)
{
    set<int> a{st.top()};
    st.pop();
    set<int> b{st.top()};
    st.pop();
	
    set<int> inter{};
    for (int elem : a)
	if (b.find(elem) != b.end())
	    inter.insert(elem);

    st.push(inter);
    return inter.size();
}

int _union(stack<set<int>>& st)
{
    set<int> a{st.top()};
    st.pop();
    set<int> b{st.top()};
    st.pop();
    
    for (int elem : a)
	b.insert(elem);	

    st.push(b);
    return b.size();
}

int add(stack<set<int>>& st, map<set<int>, int>& perfect_hash, int& index)
{
    set<int> a{st.top()};
    st.pop();
    set<int> b{st.top()};
    st.pop();
    
    int a_num;
    auto it = perfect_hash.find(a);
    if (it == perfect_hash.end())
    {
	perfect_hash[a] = ++index;
	a_num = index;	
    }
    else
	a_num = (*it).second;
    
    b.insert(a_num);
    
    st.push(b);
    
    return b.size();
}

int main()
{
    int cardinality, operations;
    cin >> cardinality;

    for(int i = 0; i < cardinality; i++)
    {
	stack<set<int>> st;
	map<set<int>, int> perfect_hash;
	perfect_hash[{}] = 0;
	perfect_hash[{0}] = 1;
	int index = 1;
	cin >> operations;
	for (int i = 0; i < operations; i++)
	{
	    string res;
	    cin >> res;
	    if (res == "PUSH")
		cout << push(st) << endl;
	    else if (res == "DUP")
		cout << dup(st) << endl;
	    else if (res == "UNION")
		cout << _union(st) << endl;
	    else if (res == "INTERSECT")
		cout << intersect(st) << endl;
	    else if (res == "ADD")
		cout << add(st, perfect_hash, index) << endl;	
	}
	cout << "***" << endl;
    }
}

#include <stack>
#include <iostream>

using namespace std;

int push(stack<int>& st)
{
    st.push(0);
    return 0;
}

int dup(stack<int>& st)
{
    int tmp{st.top()};
    st.push(tmp);
    return tmp;
}

int intersect(stack<int>& st)
{
    int a{st.top()};
    st.pop();
    int b{st.top()};
    st.pop();
	
    if (a < b)
	st.push(a);
    else
	st.push(b);
    
    return st.top();    
}

int _union(stack<int>& st)
{
    int a{st.top()};
    st.pop();
    int b{st.top()};
    st.pop();
    
    if (a > b)
	st.push(a);
    else
	st.push(b);
    
    return st.top();        
}

int add(stack<int>& st)
{
    int a{st.top()};
    st.pop();
    st.pop();
    st.push(a + 1);
    return st.top();
}

int main()
{
    int cardinality, operations;
    cin >> cardinality;

    stack<int> st;   

    for(int i = 0; i < cardinality; i++)
    {
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
		cout << add(st) << endl;	
	}
	cout << "***" << endl;
    }
}

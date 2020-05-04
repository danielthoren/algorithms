#include <vector>
#include <iostream>
#include <numeric>

#include "union_find.h"

int main()
{
    int base_set_elems; //N
    int operations;     //Q

    scanf(" %d", &base_set_elems);
    scanf(" %d", &operations);

    //STD::ios_base::sync_with_stdio(false);

    //std::cin >> base_set_elems >> operations;
    
    dalg::Union_find<int> set(base_set_elems);

    for (int i = 0; i < operations; i++)
    {
    char op;
    scanf(" %c", &op);  
    
    //  std::cin >> op;
    int a, b;
    scanf(" %d", &a);
    scanf(" %d", &b);
    //std::cin >> b >> a;

    if(op == '?')
    {
        if (set.is_joined(a, b))
        printf("yes\n");
        else
        printf("no\n");
    }
    else if (op == '=')
    {
        set.join(a, b);
    }

    //print_sets(sets);
    }
    return 0;
}

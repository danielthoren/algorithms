
#include <string>
#include <algorithm>
#include <cmath>
#include <iostream>

#include "../vec2d.h"

using namespace dalg;

int main()
{    
    Vec2d<double> p{0,0, 0.0};
    Vec2d<double> u{0,1, 0.0};
    
    Vec2d<double> pt{0.0,1.0001, 0.0};
	
    bool ret = on_line(p,u,pt);
    
    std::cout << ret << std::endl;
	
    return 0;
}

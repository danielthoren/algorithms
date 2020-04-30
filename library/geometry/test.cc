
#include <string>
#include <algorithm>
#include <cmath>
#include <iostream>

#include "point.h"
#include "line.h"
#include "polygon.h"

using namespace std;


// bool point_test()
// {
//     bool global_result{true};
    
//     //------------- Test constructor ------------- 
    
//     bool result{true};
    
//     point<int> p1{1,1};
//     point<int> p2{p1};

//     result = (p2.x == p1.x && p2.y == p1.y);
//     result = (p2 == p1);

//     if (!result)
//     {
// 	cout << "Constructor test failed" << endl;
// 	return false;
//     }

//     //------------- Test Addition ------------- 

//     result = true;
//     point<int> p3{p1 + p2};

//     result = (p3.x == p1.x + p2.x &&
// 	      p3.y == p1.y + p2.y);

//     if (!result)
// 	cout << "Addition test failed" << endl;

//     global_result = global_result && result;

//     //------------- Test substraction -------------

//     result = true;
//     point<int> p4{p1 - p2};

//     result = (p4.x == p1.x - p2.x &&
// 	      p4.y == p1.y - p2.y);

//     if (!result)
// 	cout << "Substraction test failed" << endl;    

//     global_result = global_result && result;
//     //------------- Test Length -------------
    
//     result = true;
//     double len{p1.length()};
//     result = (len == sqrt(2));
    
//     p3 = p1 - p2;     
//     result = (p3.length() == 0);

//     if (!result)
// 	cout << "Length test failed" << endl;

//     global_result = global_result && result;
//     //------------- Test comparison operators -------------

//     result = true;
   
//     result = (p3 != p2);
//     result = (p3 < p2);
//     result = (p2 > p3);
//     result = (!(p2 < p3));
//     result = (!(p3 > p2));

//     result = (p2 <= p1);
//     result = (p2 >= p1);

//     if (!result)
// 	cout << "Compairson test failed" << endl;

//     global_result = global_result && result;
//     //------------- Test Scalar (*) product -------------
//     result = true;
    
//     result = (p1 * p2 == 2);

//     if (!result)
// 	cout << "Scalar product test falied" << endl;    

//     global_result = global_result && result;
//     //------------- Test Determinant -------------
//     result = true;
    
//     result = (p1.determinant(p2) == 0);

//     if (!result)
// 	cout << "Determinant test falied" << endl;

//     global_result = global_result && result;

//     return global_result;
    
// }

// bool line_test()
// {
//     bool global_result{true};

//     bool result{true};

//     //------------- Constructor Test -------------
//     point<int> p1{0,0};
//     point<int> p2{1,1};

//     Line<int> l1{p1, p2};

//     result = (l1.p0 == p1 &&
// 	      l1.u == (p2 - p1));


//     point<int> pt{5,5};
//     Line<int> l2{p2, pt};
    
//     result = (l2.p0 == p2 &&
// 	      l2.u == pt - p2);

//     if (!result)
//     {
// 	cout << "Constructor test falied" << endl;
// 	return false;
//     }

//     global_result = global_result && result;
    
//     //------------- Parallel Test -------------
//     result = true;

//     result = l1.is_parallel(l2);

//     Line<int> l3{0,1, 1,2};

//     result = l1.is_parallel(l3);

//     Line<int> l4{0, 0, 1, -2};

//     result = !l1.is_parallel(l4);
    
//     if (!result)
// 	cout << "Parallel test falied" << endl;

//     global_result = global_result && result;
    
//     //------------- operator == & != Test -------------
//     result = true;

//     result = (l1 == l2);
//     result = (l1 != l3);
//     result = (l1 != l4);
//     result = (l3 != l4);

//     if (!result)
// 	cout << "operator == & != test falied" << endl;

//     global_result = global_result && result;    

//     //------------- Orthogonal projection Test -------------
//     result = true;

//     point<double> pt1{2, 3};
//     Line<double> line1{0,0, 1,2};

//     result = (line1.orthogonal_projection(pt1) == point<double>{8.0/5.0, 16.0/5.0});
    
//     if (!result)
// 	cout << "Orthogonal projection test falied" << endl;

//     global_result = global_result && result;

//     //------------- intersection Test -------------
//     result = true;

//     Line<double> line2{-10,0, 10,0};
//     Line<double> line3{0,-10, 0, 10};
    
//     point<double> tmp{0,0};
//     result = (line2.intersection(line3) == tmp);

//     Line<double> line4{1,1, 1,1};
//     Line<double> line5{1,1, 2,1};

//     point<double> tmp2{1.0, 1.0};
//     // result = (line4.intersection(line5) == tmp2);

//     Line<double> line6{1871,5789, 216,-517};
//     Line<double> line7{189,-518, 3851,1895};

//     point<double> tmp3{221.33, -469.70, 0.05};
//     result = (tmp3 == line6.intersection(line7));

//     if (!result)
// 	cout << "Intersection test falied" << endl;

//     global_result = global_result && result;

//     return global_result;    
// }



int main()
{
    // if (!point_test())
    // {
    // 	cout << "Point test failed!" << endl << endl;
    // }
    // if (!line_test())
    // {
    // 	cout << "Line test failed!" << endl << endl;
    // }
    if (!polygon_test())
    {
	cout << "Polygon test failed!" << endl << endl;
    }

    return 0;
}

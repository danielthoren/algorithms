
#include "../point.h"
#include "graphics.h"

namespace dg
{
    template <typename T>
    class Point
    {
    public:
	Point(T x, T y) : pt(x, y)
	    {}

	Point(dalg::Point const& pt) : pt{pt}
	    {};

	point(Point const& other) : pt{other.pt}
	    {}

	void draw(Graphics& g)
	    {
		
	    }

    private:

	dalg::Point<T> pt;
    };

}

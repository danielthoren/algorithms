#ifndef POLYGON
#error 'polygon.tcc' is not supposed to be included directly. Include 'polygon.h' instead.
#endif

template<typename T>
void dalg::Polygon<T>::add_point(dalg::Vec2d<T> const& pt, T position)
{    
    auto it = points.begin();
    it += (position + 1);
    points.insert(it, pt);
}

template<typename T>
std::vector<dalg::Vec2d<T>>& dalg::Polygon<T>::get_points()
{
    return points;
}

template <typename T>
template <typename F>
F dalg::Polygon<T>::get_area() const
{
    //If less than 3 segments then there is no area
    if (points.size() < 3)
	return 0;
    
    F area{0};
    
    for (unsigned p{0}; p < points.size() - 1; p++)
    {	
	area += cross(points[p], points[p + 1]);
    }
    area += cross(points[points.size() - 1], points[0]);

    return area/2;
}

template <typename T>
std::pair<dalg::Vec2d<T>, dalg::Vec2d<T>>
dalg::Polygon<T>::min_distance(dalg::LineSegment<T> const& linseg) const
{
    T smallest_dist{std::numeric_limits<T>::max()};
    
    std::pair<dalg::Vec2d<T>, dalg::Vec2d<T>> closest{};

    for (unsigned i{0}; i < points.size() - 1; i++)
    {
	std::pair<dalg::Vec2d<T>, dalg::Vec2d<T>> cl =
	    LineSegment<T>{points[i], points[i + 1]}.closest_points( linseg );
				   
	T dist = (cl.first - cl.second).length();
	if (dist < smallest_dist)
	{
	    smallest_dist = dist;
	    closest = cl;
	}
    }
    return closest;
}

/**
 * TODO: Implement quad tree and use for optimizing which line
 * segments needs to be compared instead of comparing all of them
 */
template <typename T>
std::pair<dalg::Vec2d<T>, dalg::Vec2d<T>>
dalg::Polygon<T>::min_distance(dalg::Polygon<T> const& other) const
{
    T smallest_dist{std::numeric_limits<T>::max()};
    
    std::pair<dalg::Vec2d<T>, dalg::Vec2d<T>> closest{};

    for (unsigned i{0}; i < other.points.size() - 1; i++)
    {
	std::pair<dalg::Vec2d<T>, dalg::Vec2d<T>> cl =
	    min_distance(LineSegment<T>{other.points[i], other.points[i + 1]} );
	
	T dist = (cl.first - cl.second).length();
	
	if (dist < smallest_dist)
	{
	    smallest_dist = dist;
	    closest = cl;
	}
    }
    return closest;
}


#ifndef DALG_POLYGON
#error 'polygon.tcc' is not supposed to be included directly. Include 'polygon.h' instead.
#endif

namespace dalg
{
    
    template<typename T>
    void Polygon<T>::add_point(Vec2d<T> const& pt, T position)
    {    
	auto it = points.begin();
	it += (position + 1);
	points.insert(it, pt);
    }

    template<typename T>
    std::vector<Vec2d<T>>& Polygon<T>::get_points()
    {
	return points;
    }

    template<typename T>
    std::vector<LineSegment<T>> Polygon<T>::get_segments() const
    {
	std::vector<LineSegment<T>> segs{};
	if (points.size() <= 1)
	{
	    return segs;
	}

	for (unsigned i{0}; i < points.size() - 1; i++)
	{
	    segs.push_back( LineSegment<T>{points[i], points[i+1]} );
	}

	if (points.size() > 2)
	{
	    segs.push_back( LineSegment<T>{points[points.size() - 1], points[0]} );
	}

	return segs;
    }

    template <typename T>
    template <typename F>
    F Polygon<T>::get_area() const
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
    std::pair<Vec2d<T>, Vec2d<T>>
    Polygon<T>::min_distance(LineSegment<T> const& linseg) const
    {
	T smallest_dist{std::numeric_limits<T>::max()};
    
	std::pair<Vec2d<T>, Vec2d<T>> closest{};

	for (unsigned i{0}; i < points.size() - 1; i++)
	{
	    std::pair<Vec2d<T>, Vec2d<T>> cl =
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
    std::pair<Vec2d<T>, Vec2d<T>>
    Polygon<T>::min_distance(Polygon<T> const& other) const
    {
	T smallest_dist{std::numeric_limits<T>::max()};
    
	std::pair<Vec2d<T>, Vec2d<T>> closest{};

	for (unsigned i{0}; i < other.points.size() - 1; i++)
	{
	    std::pair<Vec2d<T>, Vec2d<T>> cl =
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

}

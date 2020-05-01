

#ifndef POLYGON
#error 'polygon.tcc' is not supposed to be included directly. Include 'polygon.h' instead.
#endif

template<typename T>
Polygon<T>::Polygon(std::vector<Point<T>> const& points)
{
    if (points.size() >= 2)
    {
	LineSegment first(points[0], points[1]);
	segments.push_back(first);
    
	for (unsigned i{2}; i < points.size(); i++)
	{
	    LineSegment seg(segments[segments.size()-1].get_end_point(), points[i]);
	    segments.push_back(seg);
	}

	LineSegment end(segments[segments.size()-1].get_end_point(), segments[0].get_start_point());
	segments.push_back(end);
    }
}

template<typename T>
void Polygon<T>::add_point(Point<T> const& pt, T position)
{
    Point<T> start = segments[position].get_start_point();
    Point<T> end = segments[position].get_end_point();

    LineSegment<T> pt_line(start, pt);
    segments[position] = pt_line;

    LineSegment closing_line(pt, end);
    
    auto it = segments.begin();
    it += (position + 1);
    segments.insert(it, closing_line);
}

template<typename T>
std::vector<LineSegment<T>>& Polygon<T>::get_segments()
{
    return segments;
}

template <typename T>
template <typename F>
F Polygon<T>::get_area() const
{
    F area{0};

    Point<T> p1 = segments[0].get_start_point();
    
    for (unsigned p{0}; p < segments.size(); p++)
    {
	Point<T> p2 = segments[p].get_end_point();
	
	area += cross(p1, p2);

	p1 = p2;
    }
	    
    return area/2;
}

template <typename T>
std::pair<Point<T>, Point<T>>
Polygon<T>::min_distance(LineSegment<T> const& linseg) const
{
    T smallest_dist{std::numeric_limits<T>::max()};
    
    std::pair<Point<T>, Point<T>> closest{};

    for (LineSegment<T> const& lseg : segments)
    {
	std::pair<Point<T>, Point<T>> cl = linseg.closest_points(lseg);
	T dist = cl.first.distance(cl.second);
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
std::pair<Point<T>, Point<T>>
Polygon<T>::min_distance(Polygon<T> const& other) const
{
    T smallest_dist{std::numeric_limits<T>::max()};
    
    std::pair<Point<T>, Point<T>> closest{};
    
    for (LineSegment<T> const& lseg : other.segments)
    {
	std::pair<Point<T>, Point<T>> cl{ min_distance(lseg) };
	T dist = cl.first.distance(cl.second);
	
	if (dist < smallest_dist)
	{
	    smallest_dist = dist;
	    closest = cl;
	}
    }

    return closest;
}

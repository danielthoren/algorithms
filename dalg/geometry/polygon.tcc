#ifndef POLYGON
#error 'polygon.tcc' is not supposed to be included directly. Include 'polygon.h' instead.
#endif

template<typename T>
dalg::Polygon<T>::Polygon(std::vector<dalg::Vec2d<T>> const& points)
{
    if (points.size() >= 2)
    {
	dalg::LineSegment first(points[0], points[1]);
	segments.push_back(first);
    
	for (unsigned i{2}; i < points.size(); i++)
	{
	    dalg::LineSegment seg(segments[segments.size()-1].get_end_point(), points[i]);
	    segments.push_back(seg);
	}

	dalg::LineSegment end(segments[segments.size()-1].get_end_point(), segments[0].get_start_point());
	segments.push_back(end);
    }
}

template<typename T>
void dalg::Polygon<T>::add_point(dalg::Vec2d<T> const& pt, T position)
{
    dalg::Vec2d<T> start = segments[position].get_start_point();
    dalg::Vec2d<T> end = segments[position].get_end_point();

    dalg::LineSegment<T> pt_line(start, pt);
    segments[position] = pt_line;

    dalg::LineSegment closing_line(pt, end);
    
    auto it = segments.begin();
    it += (position + 1);
    segments.insert(it, closing_line);
}

template<typename T>
std::vector<dalg::LineSegment<T>>& dalg::Polygon<T>::get_segments()
{
    return segments;
}

template <typename T>
template <typename F>
F dalg::Polygon<T>::get_area() const
{
    //If less than 3 segments then there is no area
    if (segments.size() < 3)
	return 0;
    
    F area{0};

    dalg::Vec2d<T> p1 = segments[0].get_start_point();
    
    for (unsigned p{0}; p < segments.size(); p++)
    {
	dalg::Vec2d<T> p2 = segments[p].get_end_point();
	
	area += cross(p1, p2);

	p1 = p2;
    }
	    
    return area/2;
}

template <typename T>
std::pair<dalg::Vec2d<T>, dalg::Vec2d<T>>
dalg::Polygon<T>::min_distance(dalg::LineSegment<T> const& linseg) const
{
    T smallest_dist{std::numeric_limits<T>::max()};
    
    std::pair<dalg::Vec2d<T>, dalg::Vec2d<T>> closest{};

    for (dalg::LineSegment<T> const& lseg : segments)
    {
	std::pair<dalg::Vec2d<T>, dalg::Vec2d<T>> cl = linseg.closest_points(lseg);
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
    
    for (dalg::LineSegment<T> const& lseg : other.segments)
    {
	std::pair<dalg::Vec2d<T>, dalg::Vec2d<T>> cl{ min_distance(lseg) };
	T dist = (cl.first - cl.second).length();
	
	if (dist < smallest_dist)
	{
	    smallest_dist = dist;
	    closest = cl;
	}
    }

    return closest;
}

#include <vector>

#include "point.h"
#include "LineSegment.h"

#ifndef POLYGON
#define POLYGON

/**
 * Author: Daniel Thorén
 *
 * Class representing a 2d polygon 
 */
template<typename T>
class Polygon
{
public:

    Polygon() = default;

    /**
     * Constructs polygon from points
     */
    Polygon(std::vector<point<T>> const& points);

    /**
     * Adds a new point between the given point and the one in front
     * of it. Defaults to the end of the segments array
     */
    void add_point(point<T> const& pt, T position = 0);
    

    std::vector<LineSegment<T>>& get_segments();

    /**
     * Calculates the area of the polygon and returns it. Awnswer is
     * always posetive.
     *
     * Template F: Type of the area calculated, should usually be of
     *             float type
     *
     * return : The area of the polygon
     */
    template <typename F = double>
    F polygon_area() const;
	
    /**
     * Calculates the point on this polygon and the given line segment
     * that are the closest.
     *
     * other : The line segment to compare distance to
     *
     * return: The closest points on the polygon and segment in the
     *         following format:
     *         pair<point on polygon, point on segment>
     *
     */
    std::pair<point<T>, point<T>>
	      min_distance(LineSegment<T> const& linseg) const;


    /**
     * Calculates the closest points on the given polygons
     *
     * other : The other polygon
     *
     * return: The closest points on the two polygons
     */
    std::pair<point<T>, point<T>>
	      min_distance(Polygon<T> const& other) const;
    
    
private:

    std::vector<LineSegment<T>> segments{};
};

template<typename T>
Polygon<T>::Polygon(std::vector<point<T>> const& points)
{
    if (points.size() >= 2)
    {
	LineSegment first(points[0], points[1]);
	segments.push_back(first);
    
	for (int i{2}; i < points.size(); i++)
	{
	    LineSegment seg(segments[segments.size()-1].get_end_point(), points[i]);
	    segments.push_back(seg);
	}

	LineSegment end(segments[segments.size()-1].get_end_point(), segments[0].get_start_point());
	segments.push_back(end);
    }
}

template<typename T>
void Polygon<T>::add_point(point<T> const& pt, T position)
{
    point<T> start = segments[position].get_start_point();
    point<T> end = segments[position].get_end_point();

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
F Polygon<T>::polygon_area() const
{
    F area{0};

    point<T> p1 = segments[0].get_start_point();
    
    for (T p{0}; p < segments.size(); p++)
    {
	point<T> p2 = segments[p].get_end_point();
	
	area += cross(p1, p2);

	p1 = p2;
    }
	    
    return std::abs(area/2);
}

template <typename T>
std::pair<point<T>, point<T>>
Polygon<T>::min_distance(LineSegment<T> const& linseg) const
{
    T smallest_dist{std::numeric_limits<T>::max()};
    
    std::pair<point<T>, point<T>> closest{};

    for (LineSegment<T> const& lseg : segments)
    {
	std::pair<point<T>, point<T>> cl = linseg.closest_points(lseg);
	T dist = cl.first.distance(cl.second);
	if (dist < smallest_dist)
	{
	    smallest_dist = dist;
	    closest = cl;
	}
    }

    return closest;
}

template <typename T>
std::pair<point<T>, point<T>>
Polygon<T>::min_distance(Polygon<T> const& other) const
{
    T smallest_dist{std::numeric_limits<T>::max()};
    
    std::pair<point<T>, point<T>> closest{};
    
    for (LineSegment<T> const& lseg : other.segments)
    {
	std::pair<point<T>, point<T>> cl{ min_distance(lseg) };
	T dist = cl.first.distance(cl.second);
	
	if (dist < smallest_dist)
	{
	    smallest_dist = dist;
	    closest = cl;
	}
    }

    return closest;
}

#endif

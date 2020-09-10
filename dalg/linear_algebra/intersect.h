
#ifndef DALG_COLLISION
#define DALG_COLLISION

#include <optional>

#include "line_segment.h"
#include "circle.h"
#include "line.h"
#include "polygon.h"

namespace dalg
{
    /**
     * Author: Daniel Thorén
     *
     * Handles intersection between two circles. Returns a point if
     * only the boundry of the circles are intersecting, otherwise a
     * pair of points. If there is no intersection then return
     * monostate. In the unlikely event that both circles intersects
     * in all possible points then returns that circle.
     *
     * c0 : The first circle
     * c1 : The second circle
     *
     * return : monostate         : no intersection
     *          Vec2d             : Only boundry intersection
     *          pair<Vec2d, Vec2d>: Two intersection points
     *          Circle            : Intersects everywhere along the circle
     */
    template <typename T>
    std::variant<std::monostate, Vec2d<T>, std::pair<Vec2d<T>, Vec2d<T>>, Circle<T> >
    intersect(Circle<T> const& c0, Circle<T> const& c1);

    
    /**
     * Author: Daniel Thorén
     *
     * Handles collisions between a circle and a line. Returns one
     * point if line is tangent, two if it intersects in another way
     * and monostate if they do not intersect.
     *
     * c : The circle
     * l : The line
     *
     * return : monostate         : no intersection
     *          Vec2d             : Only boundry intersection
     *          pair<Vec2d, Vec2d>: Two intersection points
     */
    template <typename T>
    std::variant<std::monostate, Vec2d<T>, std::pair<Vec2d<T>, Vec2d<T>> >
    intersect(Circle<T> const& c, Line<T> const& l);

    template <typename T>
    inline std::variant<std::monostate, Vec2d<T>, std::pair<Vec2d<T>, Vec2d<T>> >
    intersect(Line<T> const& l, Circle<T> const& c);

    /**
     * Author: Daniel Thorén
     *
     * Handles collisions between a circle and a line segment. Returns
     * monostate if they do not intersect.
     *
     * c : The circle
     * l : The line segment
     *
     * return : monostate         : no intersection
     *          Vec2d             : Only boundry intersection
     *          pair<Vec2d, Vec2d>: Two intersection points
     */
    template <typename T>
    std::variant<std::monostate, Vec2d<T>, std::pair<Vec2d<T>, Vec2d<T>> >
    intersect(Circle<T> const& c, LineSegment<T> const& l);

    template <typename T>
    inline std::variant<std::monostate, Vec2d<T>, std::pair<Vec2d<T>, Vec2d<T>> >
    intersect(LineSegment<T> const& l, Circle<T> const& c);


    /**
     * Author: Daniel Thorén
     *
     * Handles collisions between two lines
     *
     * l1 : Line 1
     * l2 : Line 2
     *
     * return : monostate         : no intersection
     *          Vec2d             : Only boundry intersection
     *          Line              : l1 and l2 represent the same line
     */    
    template <typename T>
    std::variant<std::monostate, Vec2d<T>, Line<T> >
    intersect(Line<T> const& l1, Line<T> const& l2);

    /**
     * Author: Daniel Thorén
     *
     * Returns the point where l1 and l2 intersects If they
     * don't intersect then return monostate
     *
     * l1 : Line segment 1
     * l2 : Line segment 2
     *
     * return: The intersection point if there is one, else monostate
     */
    template <typename T>
    std::variant<std::monostate, Vec2d<T>, LineSegment<T>>
    intersect(LineSegment<T> const& l1, LineSegment<T> const& l2);

    /**
     * Author: Daniel Thorén
     *
     * Returns the point where l and lseg intersects If they
     * don't intersect then return monostate
     *
     * l    : Line
     * lseg : Line segment
     *
     * return: The intersection point if there is one, else monostate
     */
    template <typename T>
    std::variant<std::monostate, Vec2d<T>, LineSegment<T>>
    intersect(Line<T> const& l, LineSegment<T> const& lseg);

    template <typename T>
    std::variant<std::monostate, Vec2d<T>, LineSegment<T>>
    intersect(LineSegment<T> const& lseg, Line<T> const& l);

    /**
     * Author: Daniel Thorén
     *
     * Uses the LineSegment-LineSegment intersection method to see if
     * and how the given polygons intersect.
     *
     * Time complexity: O(n^2) n = sum( LineSegments in p1 & p2 )
     *
     * Note: This can be accomplished faster if using a quad tree to
     * remove most of the posibilities (LineSegments).
     *
     * p1    : Polygon 1
     * p2    : Polygon 2
     *
     * return: The intersection points and/or lines of p1 and p2
     */
    // template <typename T>
    // std::variant<std::monostate, Vec2d<T>> //, std::pair<std::vector<Vec2d<T>>, std::vector<LineSegment<T>>> >
    // intersect(Polygon<T> const& p1, Polygon<T> const& p2);
}

#include "intersect.tcc"

#endif

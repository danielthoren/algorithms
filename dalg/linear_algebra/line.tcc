
#ifndef DALG_LINE
#error 'line.tcc' is not supposed to be included directly. Include 'line.h' instead.
#endif

namespace dalg
{
    template <typename T>
    bool Line<T>::is_parallel(Line<T> const& other) const
    {
	return cross(u, other.u) == 0;
    }


    template <typename T>
    bool Line<T>::operator==(Line<T> const& other) const
    {
	return is_parallel(other) && std::abs( cross(u, p0 - other.p0) ) < prec;
    }

    template <typename T>
    bool Line<T>::operator!=(Line<T> const& other) const
    {
	return ! (*this == other);
    }

    template <typename T>
    Vec2d<T> project(Vec2d<T> const& pt, Line<T> const& l)
    {
	Vec2d<T> pt_t {pt - l.p0};

	Vec2d<T> res{ project(pt_t, l.u) };

	res += l.p0;

	return res;
    }


    template <typename T>
    Vec2d<T> Line<T>::intersection(Line<T> const& other) const
    {
	T t = cross(other.u, (other.p0 - p0) ) / cross(other.u, u);

	//No solution
	if (t == 0)
	{
	    return Vec2d<T>(std::numeric_limits<T>::min(),
			    std::numeric_limits<T>::min());
	}

	Vec2d<T> inter{ p0 + (t * u) };
	return inter;
    }

    template<typename T>
    Vec2d<T> Line<T>::get_start() const
    {
	return p0;
    }

    template<typename T>
    Vec2d<T> Line<T>::get_vec() const
    {
	return u;
    }
}

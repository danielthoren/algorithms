
#ifndef DALG_LINE
#error 'line.tcc' is not supposed to be included directly. Include 'line.h' instead.
#endif

namespace dalg
{
    template <typename T>
    bool Line<T>::operator==(Line<T> const& other) const
    {
	return parallel(other, *this) && std::abs( cross(u, p0 - other.p0) ) < prec;
    }

    template <typename T>
    bool Line<T>::operator!=(Line<T> const& other) const
    {
	return ! (*this == other);
    }

    template <typename T>
    bool Line<T>::on_line(Vec2d<T> const& pt) const
    {
	//This is a point, check if both points are the same
	if (std::abs(u.x) < prec && std::abs(u.y) < prec)
	{
	    return p0 == pt;
	}
    
	T t { dot( (pt - p0), u) / dot(u, u) };
	return (p0 + u * t) == pt;
    }

    template <typename T>
    bool parallel(Line<T> const& l1, Line<T> const& l2)
    {
	p_type prec = get_pref_prec(l1.prec, l2.prec);
	
	return std::abs( cross(l1.u, l2.u) ) < prec;
    }

    template <typename T>
    Vec2d<T> project(Vec2d<T> const& pt, Line<T> const& l)
    {
	Vec2d<T> pt_t {pt - l.p0};

	Vec2d<T> res{ project(pt_t, l.u) };

	res += l.p0;

	return res;
    }
}

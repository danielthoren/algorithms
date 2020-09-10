#ifndef DALG_CIRCLE
#error 'circle.tcc' is not supposed to be included directly. Include 'circle.h' instead.
#endif

namespace dalg
{
    template <typename T>
    bool Circle<T>::operator==(Circle<T> const& other) const
    {
	p_type precision = get_pref_prec(prec, other.prec);
		
	return std::abs(radius - other.radius) < precision && this->center == other.center;
    }

    template <typename T>
    bool Circle<T>::operator!=(Circle<T> const& other) const
    {
	return !(*this == other);
    }

    template <typename T>
    AABB<T> Circle<T>::get_aabb() const
    {
	Vec2d<T> max{center.x + radius, center.y + radius}; //up right corner
	Vec2d<T> min{center.x - radius, center.y - radius}; //down left corner

	return AABB{min, max};
    }

}

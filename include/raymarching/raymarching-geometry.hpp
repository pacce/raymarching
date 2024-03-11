#ifndef RAYMARCHING_GEOMETRY_HPP__
#define RAYMARCHING_GEOMETRY_HPP__

#include <geometry/geometry.hpp>

namespace raymarching {
    template <typename T>
    using Point = geometry::d3::Point<T>;

    template <typename T>
    Point<T>
    absolute(const Point<T>& p) {
        return Point<T>(std::abs(p.x()), std::abs(p.y()), std::abs(p.z()));
    }

    template <typename T>
    Point<T>
    maximum(const Point<T>& p, T value) {
        return Point<T>(
              std::max<T>(p.x(), value)
            , std::max<T>(p.y(), value)
            , std::max<T>(p.z(), value)
            );
    }

    template <typename T>
    Point<T>
    minimum(const Point<T>& p, T value) {
        return Point<T>(
              std::min<T>(p.x(), value)
            , std::min<T>(p.y(), value)
            , std::min<T>(p.z(), value)
            );
    }
} // namespace raymarching

#endif // RAYMARCHING_GEOMETRY_HPP__

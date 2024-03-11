#ifndef RAYMARCHING_SHAPE_HPP__
#define RAYMARCHING_SHAPE_HPP__

#include <variant>
#include "raymarching-geometry.hpp"

namespace raymarching {
namespace shape {
    template <typename T>
    class Sphere {
        static_assert(std::is_floating_point<T>::value);
        public:
            Sphere(const Point<T>& center, T radius)
                : center_(center)
                , radius_(radius)
            {
                if ((not std::isfinite(radius)) or (radius <= 0)) {
                    throw std::runtime_error("radius must be a finite positive number");
                }
            }

            T
            distance(const Point<T>& p) const {
                return (p - center_).norm() - radius_;
            }
        private:
            geometry::d3::Point<T>  center_;
            T                       radius_;
    };
} // namespace shape
    template <typename T>
    using Shape = std::variant<shape::Sphere<T>>;

    template <typename T>
    struct distance {
        static_assert(std::is_floating_point<T>::value);

        Point<T> point;

        T operator()(const shape::Sphere<T>& v) const { return v.distance(point); }
    };
} // namespace raymarching

#endif // RAYMARCHING_SHAPE_HPP__

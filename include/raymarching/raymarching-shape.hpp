#ifndef RAYMARCHING_SHAPE_HPP__
#define RAYMARCHING_SHAPE_HPP__

#include <geometry/geometry.hpp>

namespace raymarching {
namespace shape {
    template <typename T>
    class Sphere {
        static_assert(std::is_floating_point<T>::value);
        public:
            Sphere(const geometry::d3::Point<T>& center, T radius) 
                : center_(center)
                , radius_(radius)
            {
                if ((not std::isfinite(radius)) or (radius <= 0)) {
                    throw std::runtime_error("radius must be a finite positive number");
                }
            }

            T
            distance(const geometry::d3::Point<T>& p) const {
                return (p - center_).norm() - radius_;
            }
        private:
            geometry::d3::Point<T>  center_;
            T                       radius_;
    };
} // namespace shape
} // namespace raymarching

#endif // RAYMARCHING_SHAPE_HPP__

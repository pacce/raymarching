#ifndef RAYMARCHING_SHAPE_HPP__
#define RAYMARCHING_SHAPE_HPP__

#include <variant>
#include "raymarching-geometry.hpp"

namespace raymarching {
namespace shape {
    template <typename T>
    class Box {
        static_assert(std::is_floating_point<T>::value);
        public:
            Box(const Point<T>& center, T width, T height, T depth) 
                : center_(center) 
                , dimensions_(width, height, depth)
            {
                if ((not std::isfinite(width)) or (width <= 0)) {
                    throw std::runtime_error("width must be a finite positive number");
                }
                if ((not std::isfinite(height)) or (height <= 0)) {
                    throw std::runtime_error("height must be a finite positive number");
                }
                if ((not std::isfinite(depth)) or (depth <= 0)) {
                    throw std::runtime_error("depth must be a finite positive number");
                }
            }

            T
            distance(const Point<T>& p) const {
                Point<T> u = maximum<T>(absolute<T>(p - center_) - dimensions_, 0.0);
                return u.norm();
            }
        private:
            Point<T> center_;
            Point<T> dimensions_;
    };

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
            Point<T>    center_;
            T           radius_;
    };
} // namespace shape
    template <typename T>
    using Shape = std::variant<
          shape::Box<T>
        , shape::Sphere<T>
        >;

    template <typename T>
    struct distance {
        static_assert(std::is_floating_point<T>::value);

        Point<T> point;

        T operator()(const shape::Box<T>& v) const      { return v.distance(point); }
        T operator()(const shape::Sphere<T>& v) const   { return v.distance(point); }
    };
} // namespace raymarching

#endif // RAYMARCHING_SHAPE_HPP__

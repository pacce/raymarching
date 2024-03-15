#ifndef RAYMARCHING_HPP__
#define RAYMARCHING_HPP__

#include "raymarching-colors.hpp"
#include "raymarching-png.hpp"
#include "raymarching-shape.hpp"

namespace raymarching {
    template <typename T>
    struct Scene {
        Shape<T> shape;

        T
        distance(const Point<T>& p) const {
            return std::visit(raymarching::distance<T>{p}, shape);
        }

        Point<T>
        gradient(const Point<T>& p, T EPS = 1e-3) const {
            T x = distance(p + Point<T>::xaxis() * EPS) - distance(p - Point<T>::xaxis() * EPS);
            T y = distance(p + Point<T>::yaxis() * EPS) - distance(p - Point<T>::yaxis() * EPS);
            T z = distance(p + Point<T>::zaxis() * EPS) - distance(p - Point<T>::zaxis() * EPS);

            return Point<T>(x, y, z).normalized();
        }
    };
} // namespace raymarching

#endif // RAYMARCHING_HPP__

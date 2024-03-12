#ifndef RAYMARCHING_GEOMETRY_HPP__
#define RAYMARCHING_GEOMETRY_HPP__

#include <Eigen/Core>
#include <Eigen/Geometry>
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

namespace geometry {
    template <typename T>
    class Transformation {
        static_assert(std::is_floating_point<T>::value);
        public:
            Transformation(const Eigen::Matrix<T, 4, 4>& value) : value_(value) {}

            static Transformation<T>
            identity() {
                Eigen::Matrix<T, 4, 4> value = Eigen::Matrix<T, 4, 4>::Identity();
                return Transformation<T>(value);
            }

            static Transformation<T>
            translation(const Point<T>& p) {
                Eigen::Matrix<T, 4, 4> value = Eigen::Matrix<T, 4, 4>::Identity();
                value(0, 3) = p.x();
                value(1, 3) = p.y();
                value(2, 3) = p.z();

                return Transformation<T>(value);
            }

            static Transformation<T>
            scaling(const Point<T>& p) {
                Eigen::Matrix<T, 4, 4> value = Eigen::Matrix<T, 4, 4>::Identity();
                value(0, 0) = p.x();
                value(1, 1) = p.y();
                value(2, 2) = p.z();

                return Transformation<T>(value);
            }

            static Transformation<T>
            rotation(const Point<T>& axis, T radian) {
                Eigen::Matrix<T, 4, 4> ys = Eigen::Matrix<T, 4, 4>::Identity();

                Eigen::Vector<T, 3> u(axis.x(), axis.y(), axis.z());
                Eigen::Matrix<T, 3, 3> xs = Eigen::AngleAxis<T>(radian, u).matrix();
                
                ys(0, 0) = xs(0, 0);
                ys(0, 1) = xs(0, 1);
                ys(0, 2) = xs(0, 2);
                
                ys(1, 0) = xs(1, 0);
                ys(1, 1) = xs(1, 1);
                ys(1, 2) = xs(1, 2);

                ys(2, 0) = xs(2, 0);
                ys(2, 1) = xs(2, 1);
                ys(2, 2) = xs(2, 2);

                return Transformation<T>(ys);
            }

            operator Eigen::Matrix<T, 4, 4>() const { return value_; }

            friend Transformation<T>
            operator*(const Transformation<T>& lhs, const Transformation<T>& rhs) {
                return Transformation<T>(lhs.value_ * rhs.value_);
            }

            friend Point<T>
            operator*(const Transformation<T>& transformation, const Point<T>& p) {
                Eigen::Vector<T, 4> u(p.x(), p.y(), p.z(), 1.0f);
                Eigen::Vector<T, 4> w = transformation.value_ * u;

                return Point<T>(w(0), w(1), w(2));
            }

            friend std::ostream&
            operator<<(std::ostream& os, const Transformation<T>& v) {
                return os << v.value_;
            }
        private:
            Eigen::Matrix<T, 4, 4> value_;
    };
} // namespace geometry
} // namespace raymarching

#endif // RAYMARCHING_GEOMETRY_HPP__

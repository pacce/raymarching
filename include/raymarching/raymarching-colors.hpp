#ifndef RAYMARCHING_COLORS_HPP__
#define RAYMARCHING_COLORS_HPP__

#include <algorithm>
#include <cmath>
#include <cstdint>
#include <ostream>
#include <type_traits>

namespace raymarching {
    using Channel = uint8_t;

    template <typename T>
    class Color {
        static_assert(std::is_floating_point<T>::value);
        public:
             Color() : Color(0.0, 0.0, 0.0) {}
             Color(T r, T g, T b) 
                : r_(std::clamp<T>(r, 0.0, 1.0))
                , g_(std::clamp<T>(g, 0.0, 1.0))
                , b_(std::clamp<T>(b, 0.0, 1.0))
            {}

            friend std::ostream&
            operator<<(std::ostream& os, const Color& color) {
                os << color.r_ << ", " << color.g_ << ", " << color.b_;
                return os;
            }

            Channel r() const { return static_cast<Channel>(r_ * 255.0f);}
            Channel g() const { return static_cast<Channel>(g_ * 255.0f);}
            Channel b() const { return static_cast<Channel>(b_ * 255.0f);}

            Color<T>&
            operator*=(const T& scale) {
                r_ = std::clamp<T>(r_ * scale, 0.0, 1.0);
                g_ = std::clamp<T>(g_ * scale, 0.0, 1.0);
                b_ = std::clamp<T>(b_ * scale, 0.0, 1.0);

                return *this;
            }

            friend Color<T>
            operator*(const Color<T>& c, const T& scale) {
                Color<T> xs = c;
                xs *= scale;

                return xs;
            }

            friend Color<T>
            operator*(const T& scale, const Color<T>& c) {
                Color<T> xs = c;
                xs *= scale;

                return xs;
            }

            Color<T>&
            operator*=(const Color<T>& rhs) {
                r_ = std::clamp<T>(r_ * rhs.r_, 0.0, 1.0);
                g_ = std::clamp<T>(g_ * rhs.g_, 0.0, 1.0);
                b_ = std::clamp<T>(b_ * rhs.b_, 0.0, 1.0);

                return *this;
            }

            friend Color<T>
            operator*(const Color<T>& lhs, const Color<T>& rhs) {
                Color<T> xs = lhs;
                xs *= rhs;

                return xs;
            }

            Color<T>&
            operator+=(const Color<T>& rhs) {
                r_ = std::clamp<T>(r_ + rhs.r_, 0.0, 1.0);
                g_ = std::clamp<T>(g_ + rhs.g_, 0.0, 1.0);
                b_ = std::clamp<T>(b_ + rhs.b_, 0.0, 1.0);

                return *this;
            }

            friend Color<T>
            operator+(const Color<T>& lhs, const Color<T>& rhs) {
                Color<T> xs = lhs;
                xs += rhs;

                return xs;
            }

            Color<T>&
            gamma() {
                r_ = std::sqrt(r_);
                g_ = std::sqrt(g_);
                b_ = std::sqrt(b_);

                return *this;
            }

            static Color<T> white() { return Color<T>(1.0, 1.0, 1.0); }
            static Color<T> red()   { return Color<T>(1.0, 0.0, 0.0); }
            static Color<T> green() { return Color<T>(0.0, 1.0, 0.0); }
            static Color<T> blue()  { return Color<T>(0.0, 0.0, 1.0); }
            static Color<T> black() { return Color<T>(0.0, 0.0, 0.0); }
        private:
            T r_;
            T g_;
            T b_;
    };
} // namespace raymarching

#endif // RAYMARCHING_COLORS_HPP__

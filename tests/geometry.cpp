#include <gtest/gtest.h>
#include <rapidcheck.h>
#include <rapidcheck/gtest.h>
#include <raymarching/raymarching.hpp>

using Point             = raymarching::Point<float>;
using Transformation    = raymarching::geometry::Transformation<float>;

namespace rc {
    template<>
    struct Arbitrary<Point> {
        static Gen<Point>
        arbitrary() {
            return gen::construct<Point>(
                      gen::cast<float>(gen::inRange(-100, 100))
                    , gen::cast<float>(gen::inRange(-100, 100))
                    , gen::cast<float>(gen::inRange(-100, 100))
                    );
        }
    };
}

RC_GTEST_PROP(TRANSLATION, IDENTITY, (const Point& u)) {
    Transformation t = Transformation::translation(Point::zero());
    RC_ASSERT(t * u == u);
}

RC_GTEST_PROP(TRANSLATION, XAXIS, (const Point& u)) {
    Point v             = Point::xaxis();
    Transformation t    = Transformation::translation(v);

    RC_ASSERT(t * u == (v + u));
}

RC_GTEST_PROP(TRANSLATION, YAXIS, (const Point& u)) {
    Point v             = Point::yaxis();
    Transformation t    = Transformation::translation(v);

    RC_ASSERT(t * u == (v + u));
}

RC_GTEST_PROP(TRANSLATION, ZAXIS, (const Point& u)) {
    Point v             = Point::zaxis();
    Transformation t    = Transformation::translation(v);

    RC_ASSERT(t * u == (v + u));
}

RC_GTEST_PROP(TRANSLATION, COMPOSITION, (const Point& p)) {
    Point x = Point::xaxis();
    Point y = Point::yaxis();
    Point z = Point::zaxis();

    Transformation u    = Transformation::translation(x);
    Transformation v    = Transformation::translation(y);
    Transformation w    = Transformation::translation(z);
    Transformation t    = u * v * w;

    RC_ASSERT(t * p == (p + x + y + z));
}

RC_GTEST_PROP(SCALING, IDENTITY, (const Point& u)) {
    Point v(1.0f, 1.0f, 1.0f);

    Transformation t = Transformation::scaling(v);
    RC_ASSERT(t * u == u);
}

RC_GTEST_PROP(SCALING, XAXIS, (const Point& u)) {
    Point v(2.0f, 1.0f, 1.0f);
    Point w(
          v.x() * u.x()
        , v.y() * u.y()
        , v.z() * u.z()
        );

    Transformation t = Transformation::scaling(v);
    RC_ASSERT(t * u == w);
}

RC_GTEST_PROP(SCALING, YAXIS, (const Point& u)) {
    Point v(1.0f, 2.0f, 1.0f);
    Point w(
          v.x() * u.x()
        , v.y() * u.y()
        , v.z() * u.z()
        );

    Transformation t = Transformation::scaling(v);
    RC_ASSERT(t * u == w);
}

RC_GTEST_PROP(SCALING, ZAXIS, (const Point& u)) {
    Point v(1.0f, 1.0f, 2.0f);
    Point w(
          v.x() * u.x()
        , v.y() * u.y()
        , v.z() * u.z()
        );

    Transformation t = Transformation::scaling(v);
    RC_ASSERT(t * u == w);
}

RC_GTEST_PROP(SCALING, COMPOSITION, (const Point& p)) {
    Point x(2.0f, 1.0f, 1.0f);
    Point y(1.0f, 2.0f, 1.0f);
    Point z(1.0f, 1.0f, 2.0f);
    Point result(
          2.0f * p.x()
        , 2.0f * p.y()
        , 2.0f * p.z()
        );

    Transformation u = Transformation::scaling(x);
    Transformation v = Transformation::scaling(y);
    Transformation w = Transformation::scaling(z);

    Transformation t = u * v * w;
    RC_ASSERT(t * p == result);
}

int
main(int argc, char** argv) {
    testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}

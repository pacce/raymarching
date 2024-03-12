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

RC_GTEST_PROP(TRANSLATION, COMPOSTION, (const Point& p)) {
    Point x = Point::xaxis();
    Point y = Point::yaxis();
    Point z = Point::zaxis();

    Transformation u    = Transformation::translation(x);
    Transformation v    = Transformation::translation(y);
    Transformation w    = Transformation::translation(z);
    Transformation t    = u * v * w;

    RC_ASSERT(t * p == (p + x + y + z));
}

int
main(int argc, char** argv) {
    testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}

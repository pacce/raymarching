#include <geometry/geometry.hpp>
#include <raymarching/raymarching.hpp>
#include <variant>


using Dimension = std::size_t;
using Height    = raymarching::png::Height;
using Width     = raymarching::png::Width;
using Color     = raymarching::Color<float>;

const Width WIDTH           = 800;
const Height HEIGHT         = 600;
const Dimension DIMENSION   = WIDTH * HEIGHT;

using Point     = geometry::d3::Point<float>;
using Shape     = raymarching::Shape<float>;
using Sphere    = raymarching::shape::Sphere<float>;

const Point     ORIGIN(0.0f, 0.0f, -1.0f);
const Sphere    SPHERE(Point(0.0f, 0.0f, 5.0f), 1.0f);

inline Point
process(const Shape& s, const Point& origin, const Point& direction) {
    std::size_t STEPS   = 10;   // maximum number of iterations
    const float MINIMUM = 1e-3; // minimum distance to hit
    const float MAXIMUM = 1e+3; // maximum travel distance
    float travel        = 0.0f;

    for (std::size_t i = 0; i < STEPS; i++){
        Point current   = origin + travel * direction;
        float distance  = std::visit(raymarching::distance<float>{current}, s);

        if (distance < MINIMUM) {
            return Point::yaxis();
        } else if (distance > MAXIMUM) {
            return Point::zaxis();
        }
        travel += distance;
    }
    return Point::zaxis();
}

int
main(int, char**) {
    std::vector<Color> cs{DIMENSION, Color::red()};

    std::vector<Point> coordinates(DIMENSION, Point::zero());

    for (Height h = 0; h < HEIGHT; h++) {
    for (Width w = 0; w < WIDTH; w++) {
        float x = static_cast<float>(w) / ( static_cast<float>(WIDTH) - 1);
        float y = static_cast<float>(h) / (static_cast<float>(HEIGHT) - 1);
        float z = 0.0f;

        x = (x * 2) - 1.0f;
        y = (y * 2) - 1.0f;

        Dimension index     = w + WIDTH * h;
        coordinates[index]  = Point(x, y, z);
    }
    }

    for (Dimension i = 0; i < DIMENSION; i++) {
        Point direction = coordinates[i] - ORIGIN;
        Point marched   = process(SPHERE, ORIGIN, direction);
        cs[i]           = Color(marched.x(), marched.y(), marched.z());
    }
    raymarching::png::write("sample.png", cs, WIDTH, HEIGHT);
    return 0;
}

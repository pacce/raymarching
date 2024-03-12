#include <geometry/geometry.hpp>
#include <raymarching/raymarching.hpp>
#include <variant>

using Dimension = std::size_t;
using Height    = raymarching::png::Height;
using Width     = raymarching::png::Width;
using Color     = raymarching::Color<float>;

const Width WIDTH           = 2560;
const Height HEIGHT         = 1440;
const Dimension DIMENSION   = WIDTH * HEIGHT;

using Point     = raymarching::Point<float>;

using Shape     = raymarching::Shape<float>;
using Box       = raymarching::shape::Box<float>;
using Sphere    = raymarching::shape::Sphere<float>;

const Point     ORIGIN(0.0f, 0.0f, -1.0f);
const Box       BOX(1.0f, 1.0f, 1.0f);
const Sphere    SPHERE(1.0f);

inline Color
process(const Shape& s, const Point& origin, const Point& direction) {
    std::size_t STEPS   = 80;   // maximum number of iterations
    const float MINIMUM = 1e-3; // minimum distance to hit
    const float MAXIMUM = 1e+3; // maximum travel distance
    float travel        = 0.0f;

    for (std::size_t i = 0; i < STEPS; i++){
        Point translation(0.0f, 0.0f, 5.0f);
        Point current   = origin + travel * direction;
        float distance  = std::visit(raymarching::distance<float>{current - translation}, s);

        if (distance < MINIMUM) {
            return Color::red();
        } else if (distance > MAXIMUM) {
            return Color::black();
        }
        travel += distance;
    }
    return Color::black();
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
        cs[i]           = process(SPHERE, ORIGIN, direction);
    }
    raymarching::png::write("sample.png", cs, WIDTH, HEIGHT);
    return 0;
}

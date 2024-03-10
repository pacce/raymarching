#include <geometry/geometry.hpp>
#include <iostream>
#include <raymarching/raymarching.hpp>


using Dimension = std::size_t;
using Height    = raymarching::png::Height;
using Width     = raymarching::png::Width;
using Color     = raymarching::Color<float>;

const Width WIDTH           = 800;
const Height HEIGHT         = 600;
const Dimension DIMENSION   = WIDTH * HEIGHT;

using Point     = geometry::d3::Point<float>;

int
main(int, char**) {
    std::vector<Color> cs{DIMENSION, Color::red()};
    raymarching::png::write("sample.png", cs, WIDTH, HEIGHT);

    std::vector<Point> coordinates(DIMENSION, Point::zero());

    for (Height h = 0; h < HEIGHT; h++) {
    for (Width w = 0; w < WIDTH; w++) {
        float x = static_cast<float>(w) / ( static_cast<float>(WIDTH) - 1);
        float y = static_cast<float>(h) / (static_cast<float>(HEIGHT) - 1);
        float z = 0.0f;

        Dimension index     = w + WIDTH * h;
        coordinates[index]  = Point(x, y, z);
    }
    }
    return 0;
}

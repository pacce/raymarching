#include <raymarching/raymarching.hpp>

const raymarching::png::Width WIDTH     = 800;
const raymarching::png::Height HEIGHT   = 600;

int
main(int, char**) {
    std::vector<raymarching::Color<float>> cs{WIDTH * HEIGHT, raymarching::Color<float>::red()};
    raymarching::png::write("sample.png", cs, WIDTH, HEIGHT);
    return 0;
}

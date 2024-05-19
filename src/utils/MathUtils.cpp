#include <algorithm>
#include <SFML/System/Vector2.hpp>

float vec2_length(sf::Vector2f vec) {
    return sqrt(pow(vec.x, 2) + pow(vec.y, 2));
}

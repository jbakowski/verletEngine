#include <algorithm>
#include <SFML/System/Vector2.hpp>

float vec2_length(sf::Vector2f vec) {
    return sqrt(pow(vec.x, 2) + pow(vec.y, 2));
}

float vec2_dot_product(sf::Vector2f a, sf::Vector2f b) {
    return a.x * b.x + a.y * b.y;
}

float vec2_cross_product(sf::Vector2f a, sf::Vector2f b) {
    return a.x * b.y - a.y * b.x;
}
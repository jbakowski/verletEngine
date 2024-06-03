#include <memory>
#include <SFML/System/Vector2.hpp>
#include <MathUtils.hpp>
#include <VerletObject.hpp>
#include <Link.hpp>
#include <iostream>

Link::Link(VerletObject& a, VerletObject& b, float target_dist) : object1(a), object2(b), target_distance(target_dist) {}

void Link::apply() {
    sf::Vector2f collision_axis = object1.getPosition() - object2.getPosition();
    float distance = vec2_length(collision_axis);
    sf::Vector2f n = collision_axis / distance;
    float delta = target_distance - distance;
    if (object1.getIsStatic() == false) {
        object1.setPosition(object1.getPosition() + 0.5f * delta * n);
    };
    if (object2.getIsStatic() == false) {
        object2.setPosition(object2.getPosition() + 0.5f * delta * n);
    };
}
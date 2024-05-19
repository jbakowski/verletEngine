#include <memory>
#include <SFML/System/Vector2.hpp>
#include <MathUtils.hpp>
#include <VerletObject.hpp>
#include <Link.hpp>
#include <iostream>

Link::Link(std::shared_ptr<VerletObject> a, std::shared_ptr<VerletObject> b, float target_dist) : object1(a), object2(b), target_distance(target_dist) {}

void Link::apply() {
    sf::Vector2f collision_axis = object1->position - object2->position;
    float distance = vec2_length(collision_axis);
    sf::Vector2f n = collision_axis / distance;
    float delta = target_distance - distance;
    if (object1->isStatic == false) {
        object1->position += 0.5f * delta * n;
    };
    if (object2->isStatic == false) {
        object2->position -= 0.5f * delta * n;
    };
}
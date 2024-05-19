#include "VerletObject.hpp"
#include "MathUtils.hpp"
VerletObject::VerletObject(const sf::Vector2f& position, bool staticFlag, float dragCoeff) : position(position), previousPosition(position), acceleration(0.f, 0.f), isStatic(staticFlag), dragCoefficient(dragCoeff) {}

void VerletObject::update(float dt) {
    sf::Vector2f currentPosition = position;
    sf::Vector2f velocity = position - previousPosition;
    velocity *= (1.0f - dragCoefficient);
    position = position + velocity + 0.5f * acceleration * dt * dt;
    previousPosition = currentPosition;
    acceleration = sf::Vector2f(0, 0);
}

void VerletObject::accelerate(const sf::Vector2f& acc) {
    acceleration += acc;
}

sf::Vector2f VerletObject::getPosition() const {
    return position;
}

void VerletObject::setPosition(const sf::Vector2f& position) {
    VerletObject::position = position;
    previousPosition = position;
}
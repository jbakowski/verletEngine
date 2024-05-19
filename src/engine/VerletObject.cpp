#include <SFML/Graphics.hpp>
#include "VerletObject.hpp"
#include "MathUtils.hpp"
#include <cmath>

const float airDensity = 1.225f;
const float dragCoef = 0.47f;
const float crossSectionalArea = 5.0f;

VerletObject::VerletObject(const sf::Vector2f& position, sf::Color color, bool staticFlag, float mass) :
                            position(position),
                            previousPosition(position),
                            acceleration(0.f, 0.f),
                            isStatic(staticFlag),
                            mass(mass),
                            color(color) {}

void VerletObject::update(float dt) {
    sf::Vector2f currentPosition = position;
    sf::Vector2f velocity = (position - previousPosition) / dt;
    float velocityMagnitude = std::sqrt(velocity.x * velocity.x + velocity.y * velocity.y);
    sf::Vector2f dragForce = -0.5f * airDensity * dragCoef * crossSectionalArea * velocityMagnitude * velocity;
    sf::Vector2f accelerationDueToDrag = dragForce / mass;
    acceleration += accelerationDueToDrag;
    position = position + velocity * dt + 0.5f * (acceleration / mass) * dt * dt;
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
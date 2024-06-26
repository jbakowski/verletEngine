#include <SFML/Graphics.hpp>
#include "VerletObject.hpp"
#include "MathUtils.hpp"
#include <cmath>

// drag constants
const float airDensity = 2.5;
const float dragCoef = 0.7f;
const float crossSectionalArea = 2.5f;

// friction constants
const float frictionVelocityThreshold = 0.1f;
const float frictionStaticMu = 0.7f;
const float frictionKineticMu = 0.5f;


VerletObject::VerletObject(const sf::Vector2f& position, sf::Color color, bool isStatic, float mass, float radius) :
                            position(position),
                            previousPosition(position),
                            acceleration(0.0f, 0.0f),
                            isStatic(isStatic),
                            mass(mass),
                            normalForce(0.0f),
                            angularPosition(0.0f),
                            previousAngularPosition(0.0f),
                            angularVelocity(0.0f),
                            angularAcceleration(0.0f),
                            color(color),
                            radius(radius) {
                                // artifically lower moment of inertia, because angular velocities are too low atm
                                momentInertia = (0.5f * mass * radius * radius) / 1e9;
                            }

void VerletObject::update(float dt) {
    sf::Vector2f currentPosition = position;
    sf::Vector2f velocity = (position - previousPosition) / dt;
    float velocityMagnitude = std::sqrt(velocity.x * velocity.x + velocity.y * velocity.y);
    sf::Vector2f dragForce = -0.5f * airDensity * dragCoef * crossSectionalArea * velocityMagnitude * velocity;

    // TODO: static friction check should involve sum of all forces exerted upon the object
    // since at the moment we are only taking into account drag - it's hardcoded to dragForce
    sf::Vector2f frictionForce = sf::Vector2f(0.0f, 0.0f);
    if (velocity.x < frictionVelocityThreshold) {
        frictionForce = -dragForce;
        float frictionStaticMagnitude = std::sqrt(frictionForce.x * frictionForce.x + frictionForce.y * frictionForce.y);
        if (frictionStaticMagnitude > frictionStaticMu * normalForce) {
            frictionForce = -frictionStaticMu * normalForce * (velocity / velocityMagnitude);
        };
    } else {
        frictionForce = -frictionKineticMu * normalForce * (velocity / velocityMagnitude);
    };

    sf::Vector2f totalForces = dragForce + frictionForce;
    acceleration += totalForces / mass;
    position = position + velocity * dt + 0.5f * (acceleration / mass) * dt * dt;
    previousPosition = currentPosition;
    acceleration = sf::Vector2f(0, 0);

    float currentAngularPosition = angularPosition;
    angularVelocity += angularAcceleration * dt;
    float frictionalTorque = -frictionForce.y * radius;
    angularAcceleration = frictionalTorque / momentInertia;
    angularPosition += angularVelocity * dt + 0.5f * angularAcceleration * dt * dt;
    previousAngularPosition = currentAngularPosition;
    angularAcceleration = 0.0f;

    float angularDampening = 0.99f;
    angularVelocity *= angularDampening;
}


void VerletObject::applyAngularAcceleration(const sf::Vector2f& force, const sf::Vector2f pointOfApplication) {
    sf::Vector2f r = pointOfApplication - position;
    float torque = r.x * force.y - r.y * force.x;
    angularAcceleration += torque / momentInertia;
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

sf::Vector2f VerletObject::getPreviousPosition() {
    return previousPosition;
}

void VerletObject::setPreviousPosition(const sf::Vector2f& _previousPosition) {
    previousPosition = _previousPosition;
}

float VerletObject::getNormalForce() const {
    return normalForce;
}

void VerletObject::setNormalForce(const float normal) {
    normalForce = normal;
}

bool VerletObject::getIsStatic() const {
    return isStatic;
}

void VerletObject::setIsStatic(bool _isStatic) {
    isStatic = _isStatic;
}

float VerletObject::getMass() const {
    return mass;
}

void VerletObject::setMass(float _mass) {
    mass = _mass;
}

float VerletObject::getRadius() const {
    return radius;
}

void VerletObject::setRadius(float _radius) {
    radius = _radius;
}

float VerletObject::getAngularPosition() const {
    return angularPosition;
}

void VerletObject::setAngularPosition(float angPos) {
    angularPosition = angPos;
}

float VerletObject::getAngularVelocity() const {
    return angularVelocity;
}

void VerletObject::setAngularVelocity(float _angVel) {
    angularVelocity = _angVel;
}

float VerletObject::getMomentInertia() const {
    return momentInertia;
}

void VerletObject::setMomentInertia(float moment) {
    momentInertia = moment;
}

sf::Color VerletObject::getColor() const {
    return color;
}

void VerletObject::setColor(sf::Color _color) {
    color = _color;
}
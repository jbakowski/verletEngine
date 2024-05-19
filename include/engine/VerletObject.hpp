#pragma once
#include <SFML/System/Vector2.hpp>

class VerletObject {
    public:
        VerletObject(const sf::Vector2f& position, bool staticFlag = false, float dragCoeff = 0.0002f);

        void update(float dt);
        void accelerate(const sf::Vector2f& acc);

        sf::Vector2f getPosition() const;
        void setPosition(const sf::Vector2f& position);

        sf::Vector2f position;
        sf::Vector2f previousPosition;
        sf::Vector2f acceleration;
        float dragCoefficient;
        bool isStatic;
};
#pragma once
#include <SFML/System/Vector2.hpp>
#include <SFML/Graphics.hpp>

class VerletObject {
    public:
        VerletObject(const sf::Vector2f& position,
                    sf::Color color = sf::Color(255, 255, 255),
                    bool staticFlag = false,
                    float mass = 10.0f);

        void update(float dt);
        void accelerate(const sf::Vector2f& acc);

        sf::Vector2f getPosition() const;
        void setPosition(const sf::Vector2f& position);

        sf::Vector2f position;
        sf::Vector2f previousPosition;
        sf::Vector2f acceleration;
        float mass;
        bool isStatic;

        sf::Color color;
};
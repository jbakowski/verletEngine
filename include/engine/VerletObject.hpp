#pragma once
#include <SFML/System/Vector2.hpp>
#include <SFML/Graphics.hpp>

class VerletObject {
    public:
        VerletObject(const sf::Vector2f& position,
                    sf::Color color = sf::Color(255, 255, 255),
                    bool isStatic = false,
                    float mass = 5.0f,
                    float radius = 5.0f
        );

        void update(float dt);
        void accelerate(const sf::Vector2f& acc);
        void applyAngularAcceleration(const sf::Vector2f& force, const sf::Vector2f pointOfApplication);

        sf::Vector2f getPosition() const;
        void setPosition(const sf::Vector2f& position);

        sf::Vector2f getPreviousPosition();
        void setPreviousPosition(const sf::Vector2f& previousPosition);

        bool getIsStatic() const;
        void setIsStatic(bool isStatic);

        float getNormalForce() const;
        void setNormalForce(const float normal);

        float getMass() const;
        void setMass(float mass);

        float getRadius() const;
        void setRadius(float radius);

        float getAngularPosition() const;
        void setAngularPosition(float angPos);

        float getAngularVelocity() const;
        void setAngularVelocity(float angVel);

        float getMomentInertia() const;
        void setMomentInertia(float moment);

        sf::Color getColor() const;
        void setColor(sf::Color);

    private:
        sf::Vector2f position;
        sf::Vector2f previousPosition;
        sf::Vector2f acceleration;
        float mass;
        bool isStatic;
        float normalForce;
        float radius;
        float angularPosition;
        float previousAngularPosition;
        float angularVelocity;
        float angularAcceleration;
        float momentInertia;
        sf::Color color;
};
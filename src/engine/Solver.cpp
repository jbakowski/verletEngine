#include <algorithm>
#include <vector>
#include <Solver.hpp>
#include <MathUtils.hpp>
#include <Link.hpp>
#include <iostream>
#include <thread>

// TODO: make gravity a constant and find a way to make it a more sane number than 5000.0f

Solver::Solver(std::vector<VerletObject> _objects) : objects(_objects), regionObjects(numRegions) {}

void Solver::update(float dt) {
    const uint32_t sub_steps = 8;
    const float sub_dt = dt / static_cast<float>(sub_steps);
    for (uint32_t i = 0; i < sub_steps; i++) {
        applyGravity();
        applyConstraint();
        solveCollisions(sub_dt);
        updatePositions(sub_dt);
        applyLinks();
    };
};

void Solver::applyGravity() {
    for (auto& obj : this->objects) {
        if (obj.getIsStatic() == false) {
            obj.accelerate(sf::Vector2f(0.0f, 5000.0f));
        }
    }
};

void Solver::applyConstraint() {
    const sf::Vector2f constraint = sf::Vector2f(1200, 800);
    std::for_each(this->objects.begin(), this->objects.end(), [](VerletObject& obj) {
        auto currentPosition = obj.getPosition();
        if (currentPosition.y > 600) {
            float penetrationDepth = currentPosition.y - 600;
            auto newPosition = sf::Vector2f(currentPosition.x, 600 - penetrationDepth);
            obj.setPosition(newPosition);
            obj.setNormalForce(obj.getMass() * 5000.0f);
        } else {
            obj.setNormalForce(0.0f);
        };
    });
}

bool Solver::checkCollisions(VerletObject obj1, VerletObject obj2) {
    const sf::Vector2f collision_axis = obj1.getPosition() - obj2.getPosition();
    const float distance = vec2_length(collision_axis);
    if (distance < obj1.getRadius() + obj2.getRadius()) {
        return true;
    } else {
        return false;
    }
}

void Solver::solveCollisions(float dt) {
    const uint32_t object_count = objects.size();
    // O(n^2) - TODO: optimize if performance suffers
    for (uint32_t i = 0; i < object_count; i++) {
        auto& obj1 = objects[i];
        for (uint32_t k = i+1; k < object_count; k++) {
            auto& obj2 = objects[k];
            const sf::Vector2f collision_axis = obj1.getPosition() - obj2.getPosition();
            const float distance = vec2_length(collision_axis);
            if (distance < obj1.getRadius() + obj2.getRadius()) {
                const sf::Vector2f n = collision_axis / distance;
                float overlap = obj1.getRadius() + obj2.getRadius() - distance;
                obj1.setPosition(obj1.getPosition() + 0.5f * overlap * n);
                obj2.setPosition(obj2.getPosition() - 0.5f * overlap * n);

                // conserve momentum
                sf::Vector2f v1 = (obj1.getPosition() - obj1.getPreviousPosition()) / dt;
                sf::Vector2f v2 = (obj2.getPosition() - obj2.getPreviousPosition()) / dt;
                sf::Vector2f relativeVelocity = v1 - v2;
                float velocityAlongNormal = vec2_dot_product(relativeVelocity, n);
                if (velocityAlongNormal > 0) continue;
                float e = 0.8f;

                float j = -(1 - e) * velocityAlongNormal;
                sf::Vector2f impulse = j * n;
                obj1.setPreviousPosition(obj1.getPreviousPosition() - (1 / obj1.getMass() * impulse * dt));
                obj2.setPreviousPosition(obj2.getPreviousPosition() + (1 / obj2.getMass() * impulse * dt));
                // handle angular dynamics
                obj1.setAngularVelocity(obj1.getAngularVelocity() - (vec2_cross_product(obj1.getRadius() * n, n) * (j * 1 / obj1.getMomentInertia())));
                obj2.setAngularVelocity(obj2.getAngularVelocity() + (vec2_cross_product(obj2.getRadius() * n, n) * (j * 1 / obj2.getMomentInertia())));
            }
        }
    }
};

void Solver::updatePositions(float dt) {
    for (auto& obj : this->objects) {
        if (obj.getIsStatic() == false) {
            obj.update(dt);
        }
    }
};

void Solver::addVerletObject(const VerletObject& obj) {
    objects.push_back(obj);
}

void Solver::applyLinks() {
    for (auto& link : links) {
        link.apply();
    }
}

size_t Solver::getObjectCount() {
    return objects.size();
}
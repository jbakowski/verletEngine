#include <algorithm>
#include <vector>
#include <Solver.hpp>
#include <MathUtils.hpp>
#include <Link.hpp>
#include <iostream>

// TODO: make gravity a constant and find a way to make it a more sane number than 5000.0f

Solver::Solver(std::vector<std::shared_ptr<VerletObject>> _objects) : objects(_objects) {}

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
}

void Solver::applyGravity() {
    std::for_each(this->objects.begin(), this->objects.end(), [](std::shared_ptr<VerletObject>& obj) {
        obj->accelerate(sf::Vector2f(0.0f, 5000.0f));
    });
};

void Solver::applyConstraint() {
    const sf::Vector2f constraint = sf::Vector2f(1200, 800);
    std::for_each(this->objects.begin(), this->objects.end(), [](std::shared_ptr<VerletObject>& obj) {
        auto currentPosition = obj->getPosition();
        if (currentPosition.y > 600) {
            float penetrationDepth = currentPosition.y - 600;
            auto newPosition = sf::Vector2f(currentPosition.x, 600 - penetrationDepth);
            obj->setPosition(newPosition);
            obj->setNormalForce(obj->mass * 5000.0f);
        } else {
            obj->setNormalForce(0.0f);
        };
    });
}

void Solver::solveCollisions(float dt) {
    const uint32_t object_count = objects.size();
    // O(n^2) - TODO: optimize if performance suffers
    for (uint32_t i = 0; i < object_count; i++) {
        auto obj1 = objects[i];
        for (uint32_t k = i+1; k < object_count; k++) {
            auto obj2 = objects[k];
            const sf::Vector2f collision_axis = obj1->getPosition() - obj2->getPosition();
            const float distance = vec2_length(collision_axis);
            if (distance < obj1->radius + obj2->radius) {
                const sf::Vector2f n = collision_axis / distance;
                float overlap = obj1->radius + obj2->radius - distance;
                obj1->position += 0.5f * overlap * n;
                obj2->position -= 0.5f * overlap * n;

                // conserve momentum
                sf::Vector2f v1 = (obj1->position - obj1->previousPosition) / dt;
                sf::Vector2f v2 = (obj2->position - obj2->previousPosition) / dt;
                sf::Vector2f relativeVelocity = v1 - v2;
                float velocityAlongNormal = vec2_dot_product(relativeVelocity, n);
                // if (velocityAlongNormal > 0) continue;
                float e = 0.8f;

                float j = -(1 - e) * velocityAlongNormal;
                sf::Vector2f impulse = j * n;
                obj1->previousPosition -= (1 / obj1->mass) * impulse * dt;
                obj2->previousPosition += (1 / obj2->mass) * impulse * dt;

                // handle angular dynamics
                obj1->angularVelocity -= vec2_cross_product(obj1->radius * n, n) * (j * 1 / obj1->momentInertia);
                obj2->angularVelocity += vec2_cross_product(obj2->radius * n, n) * (j * 1 / obj2->momentInertia);
            }
        }
    }
}

void Solver::updatePositions(float dt) {
    std::for_each(this->objects.begin(), this->objects.end(), [dt](std::shared_ptr<VerletObject>& obj) {
        if (obj->isStatic == false) {
            obj->update(dt);
        };
    });
};

void Solver::applyLinks() {
    for (auto& link : links) {
        link.apply();
    }
}

void Solver::addVerletObject(const std::shared_ptr<VerletObject>& obj) {
    objects.push_back(obj);
}

void Solver::addLink(const std::shared_ptr<VerletObject>& a, const std::shared_ptr<VerletObject>& b, float target_dist) {
    links.push_back(Link(a, b, target_dist));
}
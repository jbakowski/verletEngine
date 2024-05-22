#pragma once
#include <vector>
#include <memory>
#include <SFML/System/Vector2.hpp>
#include <VerletObject.hpp>
#include <Link.hpp>

class Solver {
    public:
        Solver::Solver(std::vector<std::shared_ptr<VerletObject>> _objects);
        void update(float dt);
        void updatePositions(float dt);
        void applyGravity();
        void applyConstraint();
        void applyLinks();
        void solveCollisions(float dt);
        std::vector<std::shared_ptr<VerletObject>> objects;
        std::vector<Link> links;
        void addVerletObject(const std::shared_ptr<VerletObject>& obj);
        void addLink(const std::shared_ptr<VerletObject>& a, const std::shared_ptr<VerletObject>& b, float target_dist);
};
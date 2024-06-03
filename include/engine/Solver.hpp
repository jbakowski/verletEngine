#pragma once
#include <vector>
#include <memory>
#include <SFML/System/Vector2.hpp>
#include <VerletObject.hpp>
#include <Link.hpp>
#include <ThreadPool.hpp>

class Solver {
    public:
        Solver::Solver(std::vector<VerletObject> _objects);
        void update(float dt);
        void update_multi(float dt);

        void updatePositions(float dt);
        void updatePositions_multi(size_t start, size_t end, float dt);

        void applyGravity();
        void applyGravity_multi(size_t start, size_t end);

        void applyConstraint();
        void applyConstraint_multi(size_t start, size_t end);

        void applyLinks();

        bool checkCollisions(VerletObject obj1, VerletObject obj2);
        void solveCollisions(float dt);
        void solveCollisions_multi(float dt);

        void addVerletObject(const VerletObject& obj);
        size_t getObjectCount();

        std::vector<VerletObject> objects;
    private:
        static inline const float worldWidth = 800.0f;
        static inline const float worldHeight = 1200.0f;
        static inline const size_t numRegionsX = 4;
        static inline const size_t numRegionsY = 4;
        static inline const float regionWidth = worldWidth / numRegionsX;
        static inline const float regionHeight = worldHeight / numRegionsY;
        static inline const size_t numRegions = numRegionsX * numRegionsY;

        std::vector<Link> links;
        std::vector<std::vector<VerletObject>> regionObjects;

        ThreadPool pool { std::thread::hardware_concurrency() };
};
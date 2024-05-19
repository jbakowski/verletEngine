#pragma once
#include <memory>
#include <VerletObject.hpp>

class Link {
    public:
        Link::Link(std::shared_ptr<VerletObject> a, std::shared_ptr<VerletObject> b, float target_dist);
        std::shared_ptr<VerletObject> object1;
        std::shared_ptr<VerletObject> object2;
        float target_distance;

        void apply();
};
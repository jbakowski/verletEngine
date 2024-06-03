#pragma once
#include <memory>
#include <VerletObject.hpp>

class Link {
    public:
        Link::Link(VerletObject& a, VerletObject& b, float target_dist);
        VerletObject object1;
        VerletObject object2;
        float target_distance;

        void apply();
};
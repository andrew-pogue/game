#pragma once
#include "position.hh"

// convert into primitive: Rectangle
// Also need primitives: Circle, Triangle, Cylinder, Cone
// Complex primitives like a hexagon, polygon are a combination
// of these basic primitives.
// Shapes like a humanoid can be represented by a combination of
// complex primitives.

// Represents a rectangular area of 3D space.
struct Range {
public:

    Range(Position min, Position max)
        : min_(min)
        , max_(max)
    {
    }

    bool has(Position pos) const {
        return pos.x < max_.x
            && pos.y < max_.y
            && pos.z < max_.z
            && pos.x >= min_.x
            && pos.y >= min_.y
            && pos.z >= min_.z;
    }

private:

    Position min_, max_;

};

// more than 2 points?
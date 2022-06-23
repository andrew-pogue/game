#pragma once
#include <initializer_list>
#include <stdexcept>

struct Position {
public:

    int x, y, z;

    Position(int x, int y, int z)
        : x(x), y(y), z(z) {}

    void operator+=(const Position &other) {
        x += other.x;
        y += other.y;
        z += other.z;
    }
    
    void operator-=(const Position &other) {
        x -= other.x;
        y -= other.y;
        z -= other.z;
    }

};
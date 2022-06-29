#pragma once
#include "scene/position.hh"
#include "scene/tile.hh"
#include "scene/world.hh"

// You can get the tile using the position
// but can you get position using the id
// [chunk id][tile id]
// 4'294'967'295 chunks per world * 10'000 tiles per chunk = 42'949'672'950'000 tiles per world
class PositionComponent {
public:

    PositionComponent(int x, int y, int z, const World &world)
        : position_(x,y,z)
    {}

    Position&& get_position() { return Position(x_,y_,z_); }

private:

    Position position_;
    unsigned chunk_id, tile_id;

};
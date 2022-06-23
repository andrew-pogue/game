#pragma once

#include <array>
#include <cmath>

#include "constants.hh"
#include "position.hh"
#include "tile.hh"

// A Tile container. Represents a cubic volume in the game world.
class Chunk {
public:

    const Position origin; // The bottom left corner of the chunk.

    Chunk(const Position &&pos) 
        : origin(pos), tile_array_() {}
    
    Chunk(const Position &pos) 
        : origin(pos), tile_array_() {}

    Tile& at(const Position &pos) {
        return tile_array_.at(index_of(pos));
    }

    Tile& operator[](const Position &pos) {
        return tile_array_[index_of(pos)];
    }
    
    Tile& at(size_t i) {
        return tile_array_.at(i);
    }

    Tile& operator[](size_t i) {
        return tile_array_[i];
    }

private:

    std::array<Tile, CHUNK_WIDTH * CHUNK_HEIGHT * CHUNK_DEPTH>
        tile_array_;

    size_t index_of(const Position &pos) const {
        return pos.x - origin.x
            + (pos.y - origin.y) * CHUNK_WIDTH
            + (pos.z - origin.z) * CHUNK_WIDTH * CHUNK_HEIGHT;
    }

};
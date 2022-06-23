#pragma once

#include <array>
#include <memory>

#include "chunk.hh"
#include "constants.hh"
#include "position.hh"
#include "tile.hh"

// A Chunk container.
class Scene {
public:

    const Position origin;

    Scene(const Position &pos)
        : origin(pos), chunk_array_() {}

    Scene(const Position &&pos)
        : origin(pos), chunk_array_() {}

    Tile& at(const Position &pos) {
        return chunk_array_.at(index_of(pos))->at(pos);
    }

    Tile& operator[](const Position &pos) {
        return chunk_array_.at(index_of(pos))->at(pos);
    }

    Chunk& at(size_t i) {
        return *chunk_array_.at(i);
    }

    Chunk& operator[](size_t i) {
        return *chunk_array_[i];
    }

private:

    std::array<std::shared_ptr<Chunk>, SCENE_WIDTH * SCENE_HEIGHT * SCENE_DEPTH>
        chunk_array_;

    size_t index_of(const Position &pos) const {
        return pos.x / CHUNK_WIDTH
            + (pos.y / CHUNK_HEIGHT) * SCENE_DEPTH
            + (pos.z / CHUNK_DEPTH) * SCENE_DEPTH * SCENE_HEIGHT;
    }

};
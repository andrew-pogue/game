#pragma once
#include "scene.hh"

// Loads and generates chunk data
class World {
public:

    World(const char *file) {}
    
    // If it exists in memory, loads the chunk from file.
    // Else, generates the chunk from the seed.
    Chunk get(unsigned chunk_id);

private:

    uint32_t seed_;
    // File file_;

    Chunk load(unsigned chunk_id);
    Chunk create(unsigned chunk_id);

};
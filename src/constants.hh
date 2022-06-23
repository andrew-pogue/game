#pragma once
#include <stdint.h>
#include <bitset>

const unsigned
    CHUNK_WIDTH = 10, // in tiles
    CHUNK_HEIGHT = 10, // in tiles
    CHUNK_DEPTH = 10; // in tiles

const unsigned
    SCENE_WIDTH = 10, // in chunks
    SCENE_HEIGHT = 10, // in chunks
    SCENE_DEPTH = 10, // in chunks
    WINDOW_WIDTH = 640,
    WINDOW_HEIGHT = 480;

using id_t = unsigned;
using signature_t = std::bitset<32>;
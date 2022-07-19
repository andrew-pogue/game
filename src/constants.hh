#pragma once
#include <stdint.h>
#include <bitset>
#include <utility>

using Event = ALLEGRO_EVENT;

const unsigned
    CHUNK_WIDTH = 10, // in tiles
    CHUNK_HEIGHT = 10, // in tiles
    CHUNK_DEPTH = 10, // in tiles
    SCENE_WIDTH = 10, // in chunks
    SCENE_HEIGHT = 10, // in chunks
    SCENE_DEPTH = 10, // in chunks
    WINDOW_WIDTH = 640,
    WINDOW_HEIGHT = 480;

const int
    FLAG_ALIGN_CENTER = ALLEGRO_ALIGN_CENTER;

const int
    EVENT_DISPLAY_CLOSE = ALLEGRO_EVENT_DISPLAY_CLOSE,
    EVENT_DISPLAY_CONNECTED = ALLEGRO_EVENT_DISPLAY_CONNECTED,
    EVENT_DISPLAY_DISCONNECTED = ALLEGRO_EVENT_DISPLAY_DISCONNECTED;

const unsigned
    GLYPH = 0;

using uchar = unsigned char;
using uint = unsigned int;
using cstr = const char *;

const unsigned SPEED = 5,
    NORTH = 1,
    SOUTH = 2,
    EAST = 4,
    WEST = 8,
    UP = 16,
    DOWN = 32;
const float TILE_SIZE = 40.0f;

using ID = size_t;
using Flag = std::bitset<32>;

const Flag
    COLLIDE = 1,
    MOVE = 2;

struct Coord {
    int x=0, y=0, z=0;
};

struct DrawCoord {
    float x=0.0f, y=0.0f;
};
#pragma once
#include <array>
#include <optional>
#include <climits>
#include <utility>
#include "constants.hh"
#include "entity.hh"
#include "tile.hh"

template <int WIDTH, int HEIGHT, int DEPTH>
class Level {
public:

    // origin: the coordinates of bottom-left-most tile of the level
    Level(Coord origin)
        : origin_(origin), tiles_(), id_to_coord_()
    {
        if (debug) printf("Level::Level({%i,%i,%i})\n", origin.x, origin.y, origin.z);
        // case where WIDTH * HEIGHT * DEPTH causes int buffer overflow
        if ((size_t)WIDTH*(size_t)HEIGHT*(size_t)DEPTH > INT_MAX)
            throw "Error: Level: level too big";
        if (WIDTH < 0 || HEIGHT < 0 || DEPTH < 0)
            printf("Level: WIDTH, DEPTH, HEIGHT each must be greater than 0.\n");
    }

    ~Level() {
        if (debug) printf("Level::~Level()\n");
    }

    void add(size_t id, Flag flags, Coord coord) {
        if (debug) printf("Level::add(%zi,{%i,%i,%i})\n", id, coord.x, coord.y, coord.z);
        if (id_to_coord_.count(id))
            tile(id_to_coord_[id]).remove(id);
        tile(coord).add(id, flags);
        id_to_coord_[id] = coord;
    }

    void remove(size_t id) {
        if (debug) printf("Level::remove({%zi})\n", id);
        auto it = id_to_coord_.find(id);
        if (it == id_to_coord_.end()) return;
        tile(it->second).remove(id);
    }

    const Tile& operator[](Coord coord) const {
        if (debug) printf("Level::operator[]({%i,%i,%i})\n", coord.x, coord.y, coord.z);
        if (!is_valid(coord)) throw "Error: Level: coordinates out of range";
        return tiles_.at(tile_index(coord));
    }

    std::optional<Coord> coord_of(size_t id) const {
        if (debug) printf("Level::coord_of({%zi})\n", id);
        auto it = id_to_coord_.find(id);
        if (it == id_to_coord_.cend()) 
            throw "Error: Level: coordinates out of range";
        return {it->second};
    }

    bool is_valid(Coord coord) const {
        if (debug) printf("Level::is_valid({%i,%i,%i})\n", coord.x, coord.y, coord.z);
        return coord.x >= origin_.x
            && coord.x < origin_.x + WIDTH
            && coord.y >= origin_.y
            && coord.y < origin_.y + HEIGHT
            && coord.z >= origin_.z
            && coord.z < origin_.z + DEPTH;
    }

    static inline bool debug = false;

private:

    // The bottom left corner of the level
    const Coord origin_;
    std::array<Tile, WIDTH*HEIGHT*DEPTH> tiles_;
    std::unordered_map<size_t, Coord> id_to_coord_;

    int tile_index(Coord coord) const {
        if (debug) printf("Level::tile_index({%i,%i,%i})\n", coord.x, coord.y, coord.z);
        return coord.x - origin_.x
            + (coord.y - origin_.y) * WIDTH
            + (coord.z - origin_.z) * WIDTH * HEIGHT;
    }

    Tile& tile(Coord coord) {
        if (debug) printf("Level::tile({%i,%i,%i})\n", coord.x, coord.y, coord.z);
        if (!is_valid(coord)) throw "Error: Level: coordinates out of range";
        auto i = tile_index(coord);
        return tiles_.at(i);
    }

};
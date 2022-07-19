#pragma once
#include <utility>
#include <vector>
#include "level.hh"

// Represents the players view in game.
// Can translate the coord of an entity to its correct coord on the display.
// Can determine which entities need to be rendered.
// Can "follow" an entity if the cameras coord is updated whenever the entity moves.
class Camera {
public:

    Camera(Coord origin, float width, float height, float tilesize, DrawCoord offset = {})
        : width_(width)
        , height_(height)
        , tilesize_(tilesize)
        , origin_(origin)
        , offset_(offset)
    {
        if (debug) printf("Camera::Camera({%i,%i,%i}, %f, %f, %f, {%f,%f})\n",
            origin.x, origin.y, origin.z, width, height, tilesize, offset.x, offset.y);
    }

    bool contains(Coord coord) {
        const int 
            // half of the cameras width in tiles (rounded up)
            twidth = (int)(width_ / tilesize_ / 2.0f) + 1,
            // half of the cameras height in tiles (rounded up)
            theight = (int)(height_ / tilesize_ / 2.0f) + 1;
        return coord.z == origin_.z
            && coord.x >= origin_.x - twidth
            && coord.x <= origin_.x + twidth
            && coord.y >= origin_.y - theight
            && coord.y <= origin_.y + theight;
    }

    std::vector<Coord> range() {
        std::vector<Coord> coords;
        const int 
            // half of the cameras width in tiles (rounded up)
            twidth = (int)(width_ / tilesize_ / 2.0f) + 1,
            // half of the cameras height in tiles (rounded up)
            theight = (int)(height_ / tilesize_ / 2.0f) + 1;
        for (auto x = origin_.x - twidth; x <= origin_.x + twidth; x++) {
            for (auto y = origin_.y - theight; y <= origin_.y + theight; y++) {
                coords.push_back({x, y, origin_.z});
            }
        }
        return coords;
    }
    
    DrawCoord translate(Coord coord, DrawCoord offset={0.0f,0.0f}) {
        if (debug) printf("Camera::translate({%i,%i,%i}, {%f,%f})\n",
            coord.x, coord.y, coord.z, offset.x, offset.y);
        return {
            (float)(coord.x - origin_.x) * tilesize_ + width_ / 2.0f + offset.x,
            (float)(coord.y - origin_.y) * (-tilesize_) + height_ / 2.0f + offset.y
        };
    }

    // Gets the coordinates of the tile that the camera is centered on.
    Coord coord() const { return origin_; }
    
    // Sets the coordinates of the tile that the camera is centered on.
    void coord(Coord coord) { origin_ = coord; }
    
    // Gets the offset (in pixels) of the camera from the tile its centered on.
    DrawCoord offset() const { return offset_; }
    
    // Sets the offset (in pixels) of the camera from the tile its centered on.
    void offset(DrawCoord offset) { offset_ = offset; }

    // Gets the size (in pixels) of a tile.
    // A square tile has a height and width of this many pixels.
    float tilesize() const { return tilesize_; }
    
    // Sets the size (in pixels) of a tile, effectively zooming the camera in or out.
    // A square tile has a height and width of this many pixels.
    void tilesize(float tilesize) {
        if (tilesize < 0)
            printf("Camera: invalid value: tilesize=%f\n", tilesize);
        else tilesize_ = tilesize;
    }

    // Gets the width of the camera in pixels.
    float width() const { return width_; }

    // Sets the width of the camera in pixels.
    void width(float w) {
        if (w < 0) printf("Camera: invalid value: width=%f", w);
        width_ = w;
    }

    // Gets the height of the camera in pixels.
    float height() const { return height_; }

    // Sets the height of the camera in pixels.
    void height(float h) {
        if (h < 0) printf("Camera: invalid value: height=%f", h);
        height_ = h;
    }

    static inline bool debug = false;

private:

    // The dimensions of the camera in pixels
    float width_, height_;
    // A square tile has a height and width of this many pixels
    float tilesize_;
    // The coordinates of the tile that the camera is centered on (in tiles)
    Coord origin_;
    // The offset of the camera from the tile its centered on (in pixels)
    DrawCoord offset_;

};
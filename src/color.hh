#pragma once
#include <allegro5/allegro.h>
#include <allegro5/allegro_color.h>
#include "constants.hh"

class Color {
public:

    Color(const Color &color) 
        : color_(color.color_)
    {
    }
    
    Color(uchar r, uchar g, uchar b, uchar a = 255)
        : color_(al_map_rgba(r,g,b,a))
    {
    }
    
    Color(cstr name) 
        : color_(al_color_name(name)) 
    {
    }

    void operator=(cstr name) { color_ = al_color_name(name); }
    void operator=(const Color &other) { color_ = other.color_; }

    operator ALLEGRO_COLOR() const {return color_;}

private:

    ALLEGRO_COLOR color_;

};
#pragma once

#include <allegro5/allegro.h>
#include <allegro5/allegro_font.h>
#include <stdio.h>

#include "color.hh"
#include "font.hh"
#include "graphic.hh"

// From https://liballeg.org/a5docs/trunk/font.html#al_draw_glyph :
// "If you have to draw many glyphs at the same time,
// use al_hold_bitmap_drawing with true as the parameter, 
// before drawing the glyphs, and then call al_hold_bitmap_drawing
// again with false as a parameter when done drawing the glyphs
// to further enhance performance."

class Glyph : public Graphic {
public:

    Glyph(int codepoint, Font font, Color color, int flags=0)
        : codepoint_(codepoint)
        , color_(color)
        , font_(font)
        , flags_(flags)
    {
        if (debug) printf("Glyph::Glyph()\n");
    }

    ~Glyph() { if (debug) printf("Glyph::~Glyph()\n"); }

    void set_codepoint(int codepoint) { codepoint_ = codepoint; }
    void set_color(Color color) { color_ = color; }
    void set_font(Font font) { font_ = font; }
    void set_flags(int flags) { flags_ = flags; }

    int get_codepoint() const { return codepoint_; }
    Color get_color() const { return color_; }
    Font get_font() const { return font_; }
    int get_flags() const { return flags_; }

    void draw(float x, float y) const override {
        if (debug) printf("Glyph::draw(%f, %f)\n", x, y);
        if (flags_ & ALLEGRO_ALIGN_CENTER) {
            int bbx=0, bby=0, bbw=0, bbh=0;
            al_get_glyph_dimensions(font_, codepoint_, &bbx, &bby, &bbw, &bbh);
            x = x - (float)bbx - (float)bbw/2.0f;
            y = y - (float)bby - (float)bbh/2.0f;
        }
        
        al_draw_glyph(
            font_,
            color_,
            x, y,
            codepoint_
        );
    }

    static inline bool debug = false;

private:

    int codepoint_;
    Color color_;
    Font font_;
    int flags_;

};
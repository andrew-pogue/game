#pragma once

#include <allegro5/allegro.h>
#include <allegro5/allegro_font.h>
#include <stdio.h>

#include "alxx/color.hh"
#include "alxx/font.hh"
#include "graphic.hh"

struct Glyph : public Graphic {

    Glyph(int codepoint, Font font, Color color)
        : codepoint_(codepoint)
        , color_(color)
        , font_(font)
    {
    }

    void set_codepoint(int codepoint) { codepoint_ = codepoint; }
    void set_color(Color color) { color_ = color; }
    void set_font(Font font) { font_ = font; }

    int get_codepoint() const { return codepoint_; }
    Color get_color() const { return color_; }
    Font get_font() const { return font_; }

    void draw(float x, float y) const override {
        printf("drawing %i at (%f,%f)\n", codepoint_, x, y);
        al_draw_glyph(
            font_,
            color_,
            x, y,
            codepoint_
        );
    }

private:

    int codepoint_;
    Color color_;
    Font font_;

};
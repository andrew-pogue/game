#pragma once
#include <allegro5/allegro.h>
#include <allegro5/allegro_font.h>
#include "entity.hpp"

struct Glyph : Entity {

    Glyph(int codepoint, ALLEGRO_FONT *font, ALLEGRO_COLOR color)
        :   Entity(),
            codepoint_(codepoint),
            color_(color),
            font_(font)
    {
    }

    Glyph(int codepoint, ALLEGRO_FONT *font)
        :   Entity(),
            codepoint_(codepoint),
            color_(al_map_rgb(255,255,255)),
            font_(font)
    {
    }

    ~Glyph() {
        // Don't delete the font pointer, 
        //  that is not Glyph's responsibility.
    }

    void set_codepoint(int codepoint) {
        codepoint_ = codepoint;
    }

    void set_color(const ALLEGRO_COLOR& color) { 
        color_.r = color.r;
        color_.b = color.b;
        color_.g = color.g;
        color_.a = color.a;
    }

    void set_font(ALLEGRO_FONT *font) {
        font_ = font;
    }

    void render(float x, float y) const override {
        al_draw_glyph(
            font_,
            color_,
            x, y,
            codepoint_
        );
    }

    void update() override {
    }

private:

    int codepoint_;
    ALLEGRO_COLOR color_;
    ALLEGRO_FONT *font_;

};
#pragma once
#include <allegro5/allegro.h>
#include <allegro5/allegro_font.h>
#include "graphic.hh"
#include "alxx/font.hh"
#include "alxx/color.hh"
#include "constants.hh"

class Text : public Graphic {
public:

    const static int
        ALIGN_LEFT = ALLEGRO_ALIGN_LEFT,
        ALIGN_CENTER = ALLEGRO_ALIGN_CENTER,
        ALIGN_RIGHT = ALLEGRO_ALIGN_RIGHT,
        ALIGN_INTEGER = ALLEGRO_ALIGN_INTEGER;

    Text(cstr string, Font font, Color color, int flags)
        : string_(string)
        , font_(font)
        , color_(color)
        , flags_(flags)
    {
    }

    void draw(float x, float y) const override {
        al_draw_text(font_, color_, x, y, flags_, string_);
    }

private:

    cstr string_;
    Font font_;
    Color color_;
    int flags_;

};
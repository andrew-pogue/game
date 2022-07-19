#pragma once
#include <allegro5/allegro.h>
#include <allegro5/allegro_primitives.h>
#include "graphic.hh"

class Grid : public Graphic {
public:

    static const int
        ALIGN_CENTER = 1;

    Grid(float w, float h, Color color, float spacing, float thickness, int flags=0)
        : w_(w), h_(h)
        , color_(color)
        , spacing_(spacing), thickness_(thickness)
        , flags_(flags)
    {}

    void draw(float x, float y) const override {
        if (flags_ & ALIGN_CENTER) {
            this->center_draw(x,y);
            return;
        }

        for (float i = x; i <= x + w_; i += spacing_) {
            al_draw_line(i, y, i, y + h_, color_, thickness_);
        }

        for (float j = y; j <= y + h_; j += spacing_) {
            al_draw_line(x, j, x + w_, j, color_, thickness_);
        }
    }

private:

    void center_draw(float x, float y) const {
        for (float i = x + spacing_/2.0f; i <= x + w_/2.0f; i += spacing_) {
            al_draw_line(i, y - h_/2.0f, i, y + h_/2.0f, color_, thickness_);
        }

        for (float i = x - spacing_/2.0f; i >= x - w_/2.0f; i -= spacing_) {
            al_draw_line(i, y - h_/2.0f, i, y + h_/2.0f, color_, thickness_);
        }

        for (float j = y + spacing_/2.0f; j <= y + h_/2.0f; j += spacing_) {
            al_draw_line(x - w_/2.0f, j, x + w_/2.0f, j, color_, thickness_);
        }

        for (float j = y - spacing_/2.0f; j >= y - h_/2.0f; j -= spacing_) {
            al_draw_line(x - w_/2.0f, j, x + w_/2.0f, j, color_, thickness_);
        }
    }

    float w_, h_;
    Color color_;
    float spacing_, thickness_;
    int flags_;

};
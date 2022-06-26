#pragma once
#include <allegro5/allegro.h>
#include <allegro5/allegro_color.h>
#include "component.hh"

class Graphic : public Component {
public:

    virtual ~Graphic() {}
    virtual void draw(float x, float y) const = 0;

private:

};
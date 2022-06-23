#pragma once

#include <allegro5/allegro.h>

#include "input_device.hh"

class Mouse : public io::InputDevice<20> {
public:

    // Updates the status of the mouses buttons, wheel, and/or position
    // if the given event implies it.
    void update(const ALLEGRO_EVENT &event) override {
        switch (event.type) {
        case ALLEGRO_EVENT_MOUSE_AXES:
            x_ = event.mouse.x;
            y_ = event.mouse.y;
            z_ = event.mouse.z;
            dx_ = event.mouse.dx;
            dy_ = event.mouse.dy;
            dz_ = event.mouse.dz;
            break;
        case ALLEGRO_EVENT_MOUSE_BUTTON_DOWN:
            set_key_pressed(event.mouse.button);
            break;
        case ALLEGRO_EVENT_MOUSE_BUTTON_UP:
            set_key_released(event.mouse.button);
            break;
        case ALLEGRO_EVENT_MOUSE_ENTER_DISPLAY:
            is_enabled_ = true;
            break;
        case ALLEGRO_EVENT_MOUSE_LEAVE_DISPLAY:
            is_enabled_ = false;
            break;
        }
    }

    Mouse(int x, int y, int z=0) 
        : x_(x), y_(y), z_(z)
        , dx_(0), dy_(0), dz_(0)
        , is_enabled_(/*x and y are within display*/) 
    {
    }

    const int&
        x = x_,
        y = y_,
        z = z_,
        dx = dx_,
        dy = dy_,
        dz = dz_;
    const bool &is_enabled = is_enabled_;

private:

    int x_, y_, z_,
        dx_, dy_, dz_;
    bool is_enabled_;

}; // class Mouse
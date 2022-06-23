#pragma once

#include <allegro5/allegro.h>

#include "input_device.hh"

class Keyboard : public io::InputDevice<ALLEGRO_KEY_MAX> {
public:

    // Updates a key's status if the given event implies it.
    void update(const ALLEGRO_EVENT &event) override {
        // Hardcoded key responses/commands can go here
        switch (event.type) {
        case ALLEGRO_EVENT_KEY_DOWN:
            this->set_key_pressed(event.keyboard.keycode);
            break;
        case ALLEGRO_EVENT_KEY_UP:
            this->set_key_released(event.keyboard.keycode);
            break;
        }
    }

}; // class Keyboard
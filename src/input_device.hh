#pragma once

#include <allegro5/allegro.h> // for ALLEGRO_EVENT
#include <array>
#include <functional>

template <int KEY_MAX>
class InputDevice;

using Keyboard = InputDevice<ALLEGRO_KEY_MAX>;
using Mouse = InputDevice<20>;

// This class logs the status of the keys/buttons of an input device
// and maps those keys to a function.
template <int KEY_MAX>
class InputDevice {
public:

    // By default, every key is initialized to an empty function.
    // An empty function is a function that does nothing.
    InputDevice()
        : log_()
        , functions_() 
    {
        if (debug) printf("InputDevice::InputDevice()\n");
    }

    // Runs each function that is mapped to a key that has been pressed.
    void progress(size_t id) {
        if (debug) printf("InputDevice::progress(%zi)\n", id);
        for (int keycode = 0; keycode < KEY_MAX; keycode++) {
            if (was_pressed(keycode)) {
                if(functions_[keycode]) functions_[keycode](id);
                set_key_seen(keycode);
            }
        }
    }

    // Returns a reference to the function mapped to the key.
    // Throws an std::out_of_range exception if the keycode is out of bounds.
    auto& on_input(int keycode) {
        if (debug) printf("InputDevice::on_input(%i)\n", keycode);
        return functions_.at(keycode);
    }

    // Returns true if the key was activated since the last step.
    bool was_pressed(int keycode) const {
        return this->log_[keycode];
    }

    // Returns true if the keys status changed from *de-active* to *active* in-between
    // this step and the previous step.
    bool was_just_pressed(int keycode) const {
        return this->log_[keycode] & (KEY_PRESSED | NOT_SEEN);
    }
    
    // Returns true if the keys status changed from *active* to *de-active* in-between
    // this step and the previous step.
    bool was_just_released(int keycode) const {
        return !(this->log_[keycode] & KEY_PRESSED)
            && this->log_[keycode] & NOT_SEEN;
    }

    // Returns true if the keys status has remained *active* in-between this step and
    // the previous step.
    bool has_remained_pressed(int keycode) const {
        return this->log_[keycode] & KEY_PRESSED
            && !(this->log_[keycode] & NOT_SEEN);
    }
    
    // This keys change in status has been accounted for.
    // This is necessary so that a key pressed and released in-between steps isn't missed.
    void set_key_seen(int keycode) {
        this->log_[keycode] &= KEY_PRESSED;
    }

    // Any new unseen key status is no longer new and unseen.
    void all_keys_seen() {
        for(int keycode = 0; keycode < KEY_MAX; keycode++) {
            this->key_seen(keycode);
        }
    }

    // This key was activated since last update.
    // Should be called when a key-press event occurs.
    void set_key_pressed(int keycode) {
        this->log_[keycode] = KEY_PRESSED | NOT_SEEN;
    }

    // This key was de-activated since last update.
    // Should be called when a key-release event occurs.
    void set_key_released(int keycode) {
        this->log_[keycode] &= NOT_SEEN;
    }

    static inline bool debug = false;

private:

    // The index represents the keycode of a key or button on the associated input device.
    // The value represents the status of that key.
    std::array<unsigned char, KEY_MAX> log_;

    // The index represents the keycode of a key or button on the associated input device.
    // Stored at that index is the function bound to that key.
    std::array<std::function<void(size_t)>, KEY_MAX> functions_;

    static const unsigned char
        // ticked if the key is or was pressed
        KEY_PRESSED  = 1,
        // ticked if the key's new status hasn't been seen
        NOT_SEEN = 2;

    /** This is a little confusing. It's based on the Allegro Vivace tutorial.
     * Chars in this array should only be one of these 4 values:
     * 00000011 (3) ----> key pressed,      not seen        'was just pressed'
     * 00000001 (1) ----> key pressed,      seen            'has remained pressed'
     * 00000010 (2) ----> key released,     not seen        'was just released'
     * 00000000 (0) ----> key released,     seen            'was not pressed'
     **/

}; // class InputDevice
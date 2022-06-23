#pragma once

#include <allegro5/allegro.h> // for ALLEGRO_EVENT
#include <array>

#include "command.hh"

namespace io {

    // This class is used to log the status of the keys on an input device
    // such that a pressed key cannot be missed by the input handler.
    // Without this, a key could be tapped and released in-between frames
    // and the input handler wouldn't know. It also allows the input handler
    // to deduce if a key was 'just pressed', 'just released', or 'remained pressed'.
    template <size_t SIZE>
    class InputDevice {
    public:

        // By default, every key is initialized to an empty command.
        // An empty command is a command that does nothing.
        InputDevice();

        // Updates a key's status if the given event implies it.
        virtual void update(const ALLEGRO_EVENT &event) = 0;

        // Gets all the commands issued since get_commands()
        // was last called.
        auto get_commands();

        // Gets a reference to the command bound to the given input keycode.
        Command& operator[](int keycode);

    protected:
        
        // Returns true if the key is/was activate/activated since the last frame.
        bool was_pressed(int keycode) const;

        // Returns true if the key's status changed from *de-active* to *active* in-between
        // this frame and the previous frame, and the entry was *not seen* by an input handler.
        bool was_just_pressed(int keycode) const;
        
        // Returns true if the key's status changed from *active* to *de-active* in-between
        // this frame and the previous frame, and the entry was *not seen* by an input handler.
        bool was_just_released(int keycode) const;

        // Returns true if the key's status has remained *active* in-between this frame and
        // the previous frame, and the entry was *seen* by an input handler in either
        // this frame or in a previous frame.
        bool has_remained_pressed(int keycode) const;
        
        // Flags the key as handled by an input handler. This is necessary so that, in future
        // frames, we can deduce if the key 'has remained pressed'. It also resets a 'just
        // released' key so that, in future frames, it is flagged as 'was not pressed'.
        void key_handled(int keycode);

        // Flags all keys as handled by an input handler. Should be called once per
        // frame at the end of input handling unless you want a key to remain flagged
        // as 'was pressed'.
        void all_keys_handled();

        // Should be called when a key press event occurs.
        void set_key_pressed(int keycode);

        // Should be called when a key release event occurs.
        void set_key_released(int keycode);

    private:

        // The index of the array represents the key code of a key on the keyboard.
        // The value stored at that index represents the status of that key.
        // If the status is equal to 0, the key has not been activated.
        // Else, the key has been or remaind activated since the log was last updated.
        std::array<unsigned char, SIZE> log_;

        // The index of the array represents the key code of a key on the keyboard.
        // Stored at that index is the command bound to that key.
        std::array<Command, SIZE> commands_;

        /**
         * This is confusing. It's based on the Allegro Vivace tutorial.
         * 
         * 00000001 (1) ----> key pressed
         * 00000010 (2) ----> not seen
         * 
         * Chars in this array should only be one of these 4 values:
         * 00000011 (3) ----> key pressed,      not seen        'was just pressed'
         * 00000001 (1) ----> key pressed,      seen            'has remained pressed'
         * 00000010 (2) ----> key released,     not seen        'was just released'
         * 00000000 (0) ----> key released,     seen            'was not pressed'
         * 
         * 'seen' -------> key has been accounted for by an input handler since being pressed
         * 'pressed' ----> key was activated since last frame
         * 'released' ---> key was de-activated since last frame
         * 'was pressed' > not 'was not pressed'
         **/

    }; // class InputDevice

} // namespace io
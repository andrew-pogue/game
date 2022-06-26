#pragma once

#include <allegro5/allegro.h> // for ALLEGRO_EVENT
#include <array>
#include <iostream>

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
        InputDevice()
            : log_()
            , commands_() 
        {
        }

        virtual ~InputDevice() { printf("~InputDevice()\n"); }

        // Updates a key's status if the given event implies it.
        virtual void update(const ALLEGRO_EVENT &event) = 0;

        // Gets all the commands issued since get_commands()
        // was last called.
        auto get_commands() {
        std::vector<Command> commands = {};

            for (size_t key = 0; key < SIZE; key++) {
                if (this->was_pressed((int)key)) {
                    commands.push_back(commands_[key]);
                    this->key_handled((int)key);
                }
            }

            return commands;
        }

        // Gets a reference to the command bound to the given input keycode.
        Command& operator[](int keycode) {
            return commands_[keycode];
        }

    protected:
        
        // Returns true if the key is/was activate/activated since the last frame.
        bool was_pressed(int keycode) const {
            return this->log_[keycode];
        }

        // Returns true if the key's status changed from *de-active* to *active* in-between
        // this frame and the previous frame, and the entry was *not seen* by an input handler.
        bool was_just_pressed(int keycode) const {
            return this->log_[keycode] & (KEY_PRESSED | NOT_SEEN);
        }
        
        // Returns true if the key's status changed from *active* to *de-active* in-between
        // this frame and the previous frame, and the entry was *not seen* by an input handler.
        bool was_just_released(int keycode) const {
            return !(this->log_[keycode] & KEY_PRESSED)
                && this->log_[keycode] & NOT_SEEN;
        }

        // Returns true if the key's status has remained *active* in-between this frame and
        // the previous frame, and the entry was *seen* by an input handler in either
        // this frame or in a previous frame.
        bool has_remained_pressed(int keycode) const {
            return this->log_[keycode] & KEY_PRESSED
                && !(this->log_[keycode] & NOT_SEEN);
        }
        
        // Flags the key as handled by an input handler. This is necessary so that, in future
        // frames, we can deduce if the key 'has remained pressed'. It also resets a 'just
        // released' key so that, in future frames, it is flagged as 'was not pressed'.
        void key_handled(int keycode) {
            this->log_[keycode] &= KEY_PRESSED;
        }

        // Flags all keys as handled by an input handler. Should be called once per
        // frame at the end of input handling unless you want a key to remain flagged
        // as 'was pressed'.
        void all_keys_handled() {
            for(int key = 0; key < SIZE; key++) {
                this->key_handled(key);
            }
        }

        // Should be called when a key press event occurs.
        void set_key_pressed(int keycode) {
            this->log_[keycode] = KEY_PRESSED | NOT_SEEN;
        }

        // Should be called when a key release event occurs.
        void set_key_released(int keycode) {
            this->log_[keycode] &= NOT_SEEN;
        }

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

        static const unsigned char
            // The first bit is ticked if the key is or was pressed.
            KEY_PRESSED  = 1,
            // The second bit is ticked if the key's new status has 
            // not been seen by an input handler.
            NOT_SEEN = 2;

    }; // class InputDevice

} // namespace io
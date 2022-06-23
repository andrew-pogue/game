#include "input_device.hh"

// TO DO: inputlog is now template, need to move definitions to header

static const unsigned char
    // The first bit is ticked if the key is or was pressed.
    KEY_PRESSED  = 1,
    // The second bit is ticked if the key's new status has 
    // not been seen by an input handler.
    NOT_SEEN = 2;

namespace io {

    // =========== / InputDevice Public API / ===================================

    template <size_t SIZE>
    InputDevice<SIZE>::InputDevice()
        : log_()
        , commands_() 
    {
    }

    template <size_t SIZE>
    auto InputDevice<SIZE>::get_commands() {
        std::vector<Command> commands = {};

        for (int key = 0; key < SIZE; key++) {
            if (this->was_pressed(key)) {
                commands.push_back(commands_[key]);
                this->key_handled(key);
            }
        }

        return commands;
    }

    template <size_t SIZE>
    Command& InputDevice<SIZE>::operator[](int keycode) {
        return commands_[keycode];
    }

    // =========== / InputDevice Protected API / ===================================

    template <size_t SIZE>
    bool InputDevice<SIZE>::was_pressed(int keycode) const {
        return this->log_[keycode];
    }

    template <size_t SIZE>
    bool InputDevice<SIZE>::was_just_pressed(int keycode) const {
        return this->log_[keycode] & (KEY_PRESSED | NOT_SEEN);
    }

    template <size_t SIZE>
    bool InputDevice<SIZE>::was_just_released(int keycode) const {
        return !(this->log_[keycode] & KEY_PRESSED)
            && this->log_[keycode] & NOT_SEEN;
    }

    template <size_t SIZE>
    bool InputDevice<SIZE>::has_remained_pressed(int keycode) const {
        return this->log_[keycode] & KEY_PRESSED
            && !(this->log_[keycode] & NOT_SEEN);
    }

    template <size_t SIZE>
    void InputDevice<SIZE>::key_handled(int keycode) {
        this->log_[keycode] &= KEY_PRESSED;
    }

    template <size_t SIZE>
    void InputDevice<SIZE>::all_keys_handled() {
        for(int key = 0; key < SIZE; key++) {
            this->key_handled(key);
        }
    }

    template <size_t SIZE>
    void InputDevice<SIZE>::set_key_pressed(int keycode) {
        this->log_[keycode] = KEY_PRESSED | NOT_SEEN;
    }

    template <size_t SIZE>
    void InputDevice<SIZE>::set_key_released(int keycode) {
        this->log_[keycode] &= NOT_SEEN;
    }

} // namespace io
#pragma once
#include <allegro5/allegro.h>
#include <stdio.h>
#include "../io/input_device.hh"

// Wrapper for ALLEGRO_DISPLAY
class Display : public io::InputDevice<62> {
public:

    Display(int width, int height);
    Display(int width, int height, const char *title);
    ~Display();

    int get_height() const;
    int get_width() const;

    void set_title(const char *title);

    operator ALLEGRO_DISPLAY* ();
    operator ALLEGRO_EVENT_SOURCE* ();

    void update(const ALLEGRO_EVENT &event) override;
    
    static int get_default_flags();
    static int get_default_option(int option, int *importance);

    static void set_default_flags(int flags);
    static void set_default_option(int option, int value, int importance);
    static void reset_default_options();

private:

    ALLEGRO_DISPLAY* display_;

};
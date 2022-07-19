#pragma once
#include <allegro5/allegro.h>
#include <stdio.h>
#include <utility>

// Wrapper for ALLEGRO_DISPLAY
class Display {
public:

    Display(int width, int height);
    Display(int width, int height, const char *title);
    ~Display();

    int height() const;
    int width() const;

    void set_title(const char *title);

    operator ALLEGRO_DISPLAY* ();
    operator ALLEGRO_EVENT_SOURCE* ();
    
    static int get_default_flags();
    static int get_default_option(int option, int *importance);

    static void set_default_flags(int flags);
    static void set_default_option(int option, int value, int importance);
    static void reset_default_options();

private:

    ALLEGRO_DISPLAY* display_;

};
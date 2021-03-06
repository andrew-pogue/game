#include "display.hh"

// ================ / PUBLIC API / ===============================================

Display::Display(int width, int height)
    : display_(al_create_display(width, height))
{
    if (!display_) throw "Error: failed to create display.";
}

Display::Display(int width, int height, const char *title)
    : display_(al_create_display(width, height))
{
    if (!display_) throw "Error: failed to create display.";
    this->set_title(title);
}

Display::~Display() {
    al_destroy_display(display_);
    /*
        If the target bitmap of the calling thread is tied to the display,
        then it implies a call to “al_set_target_bitmap(NULL);” before the 
        display is destroyed.

        That special case notwithstanding, you should make sure no threads are
        currently targeting a bitmap which is tied to the display before you
        destroy it.
    */
}

int Display::height() const {
    return al_get_display_height(display_);
}

int Display::width() const {
    return al_get_display_width(display_);
}

void Display::set_title(const char *title) {
    al_set_window_title(display_, title);
}

Display::operator ALLEGRO_DISPLAY* () {
    return display_;
}

Display::operator ALLEGRO_EVENT_SOURCE* () {
    return al_get_display_event_source(display_);
}

// ================ / STATIC API / ===============================================

// Get the display flags to be used when creating new displays on the calling thread.
int Display::get_default_flags() {
    return al_get_new_display_flags();
}

int Display::get_default_option(int option, int *importance) {
    return al_get_new_display_option(option, importance);
}

// Sets various flags to be used when creating new displays on the calling thread.
void Display::set_default_flags(int flags) {
    al_set_new_display_flags(flags);
}

void Display::set_default_option(int option, int value, int importance) {
    al_set_new_display_option(option, value, importance);
}

void Display::reset_default_options() {
    al_reset_new_display_options();
}
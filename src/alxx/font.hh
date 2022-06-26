#pragma once
#include <allegro5/allegro.h>
#include <allegro5/allegro_font.h>

class Font {
public:

    Font(ALLEGRO_FONT *font) : name_(""), font_(font) {}
    operator const ALLEGRO_FONT*() const { return font_; }

protected:

    cstr name_;
    ALLEGRO_FONT *font_;

private:

};
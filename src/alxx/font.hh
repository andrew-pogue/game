#pragma once
#include <allegro5/allegro.h>
#include <allegro5/allegro_font.h>
#include <allegro5/allegro_ttf.h>
#include <memory.h>
#include <stdio.h>
#include <string>
#include "../util.hh"

class Font {
public:

    Font(cstr path, int size, int flags=0)
        : path_(path)
        , name_(get_filename(path))
        , size_(size)
        , flags_(flags)
        , font_(al_load_font(path, size, flags), AllegroFontDeleter())
    {
    }

    Font(const Font &other) 
        : path_(other.path_)
        , name_(other.name_)
        , size_(other.size_)
        , flags_(other.flags_)
        , font_(other.font_)
    {
    }

    void operator=(const Font &other) {
        path_ = other.path_;
        name_ = other.name_;
        size_ = other.size_;
        flags_ = other.flags_;
        font_ = other.font_;
    }

    cstr path() const { return path_; }
    cstr name() const { return name_; }
    int size() const { return size_; }
    int flags() const { return flags_; }

    operator const ALLEGRO_FONT*() const { return font_.get(); }
    operator bool() const { return (bool)font_; }

protected:

    cstr path_, name_;
    int size_, flags_;
    std::shared_ptr<ALLEGRO_FONT> font_;

    struct AllegroFontDeleter {
        void operator()(ALLEGRO_FONT *font) {
            printf("AllegreFontDeleter called\n");
            al_destroy_font(font);
        }
    };

};
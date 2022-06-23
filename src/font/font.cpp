#include "font.hpp"

static const bool DEBUG = true;

// ================= / PUBLIC API / ======================================

FontManager::FontManager() 
    : font_vector_(), path_map_()
{
    if (DEBUG) printf("FontManager::FontManager()\n");
    load_builtin();
}

FontManager::~FontManager() {
    if (DEBUG) printf("FontManager::~FontManager()\n");
    for (auto font : font_vector_) {
        al_destroy_font(font);
    }
}

int FontManager::size() const {
    return font_vector_.size();
}

unsigned short FontManager::index_of(const std::string &path) const {
    return path_map_.at(path);
}

ALLEGRO_FONT* FontManager::operator[](const std::string &path) {
    return font_vector_.at(path_map_.at(path));
}

ALLEGRO_FONT* FontManager::operator[](size_t i) {
    return font_vector_.at(i);
}

bool FontManager::load_font(const std::string &path, int size) {
    if (DEBUG) printf("FontManager::load_font(%s, %i)\n", path.c_str(), size);

    if (path.size() == 0) {
        if (DEBUG) printf("\tNo action needed: Path is empty string.\n");
        return true;
    }

    if (path_map_.find(path) != path_map_.end()) {
        if (DEBUG) printf("\tNo action needed: Font already loaded.\n");
        return true;
    }

    ALLEGRO_FONT* font = al_load_font(path.c_str(), size, ALLEGRO_ALIGN_CENTER);
    if (font) {
        if (DEBUG) printf("\tLoaded font.");
        path_map_[path] = font_vector_.size();
        font_vector_.push_back(font);
        if (DEBUG) printf("\tMapped path to index %zi.", font_vector_.size());
        return true;
    }
    if (DEBUG) printf("\tFailed to load font.\n");
    return false;
}

bool FontManager::load_bmp(const std::string &path) {
    if (DEBUG) printf("FontManager::load_bmp(%s)\n", path.c_str());

    if (path.empty())
        return true;
    if (path_map_.find(path) != path_map_.end())
        return true;

    ALLEGRO_FONT* font = al_load_bitmap_font(path.c_str());
    if (font) {
        path_map_[path] = font_vector_.size();
        font_vector_.push_back(font);
        return true;
    }
    return false;
}

bool FontManager::load_ttf(const std::string &path, int size) {
    if (DEBUG) printf("FontManager::load_ttf(%s, %i)\n", path.c_str(), size);

    if (path.size() == 0)
        return true;
    if (path_map_.find(path) != path_map_.end())
        return true;

    ALLEGRO_FONT* font = al_load_ttf_font(path.c_str(), size, ALLEGRO_ALIGN_CENTER);
    if (font) {
        path_map_[path] = font_vector_.size();
        font_vector_.push_back(font);
        return true;
    }
    return false;
}

// ================= / PRIVATE API / ======================================

bool FontManager::load_builtin() {
    if (DEBUG) printf("FontManager::load_builtin()\n");

    ALLEGRO_FONT* font = al_create_builtin_font();
    if (font) {
        path_map_[""] = font_vector_.size();
        font_vector_.push_back(font);
        return true;
    }
    return false;
}
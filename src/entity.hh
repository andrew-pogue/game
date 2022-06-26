#pragma once
#include "constants.hh"
#include "graphic.hh"
#include "property.hh"
#include <memory>
#include <iostream>
#include <vector>

class Entity {
public:

    Entity(cstr name, id_t id, signature_t sign = signature_t())
        : name_(name), id_(id), sign_(sign), graphics_() {}

    void update() {
        for (auto property : properties_) {
            property->progress();
        }
    };

    // get tiles to render from camera
    // then translate tile position to display position
    // then get entities to render from tile
    // then pass display position to entities render(x,y)
    void render(float x, float y) const {
        printf("rendering %s\n", name_);
        for (auto graphic : graphics_) {
            graphic->draw(x,y);
        }
    };

    void operator+=(Graphic *graphic) {
        graphics_.emplace_back(graphic);
    }

    void operator+=(Property *property) {
        properties_.emplace_back(property);
    }


    id_t get_id() const { return id_; }
    signature_t get_signature() const { return sign_; }

private:

    cstr name_;
    id_t id_;
    signature_t sign_;

    std::vector<std::shared_ptr<Graphic>> graphics_;
    std::vector<std::shared_ptr<Property>> properties_;

};
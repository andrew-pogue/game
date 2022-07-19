#pragma once
#include "constants.hh"
#include "graphic.hh"
#include "property.hh"
#include <iostream>
#include <memory>
#include <vector>

class Entity {
public:

    Entity(size_t id, Flag flags = 0)
        : id_(id)
        , flags_(flags)
        , graphics_()
        , properties_()
    {
        if (debug) printf("Entity::Entity(%zi)\n", id);
    }

    Entity(Entity &&other) 
        : id_(other.id_)
        , flags_(other.flags_)
        , graphics_(std::move(other.graphics_))
        , properties_(std::move(other.properties_))
    {
        if (debug) printf("Entity::Entity(&&{%zi})\n", other.id_);
    }

    Entity(const Entity &other) 
        : id_(other.id_)
        , flags_(other.flags_)
        , graphics_(other.graphics_)
        , properties_(other.properties_)
    {
        if (debug) printf("Entity::Entity(&{%zi})\n", other.id_);
    }

    ~Entity() {
        if (debug) printf("Entity::~Entity(%zi)\n", id_);
    }

    void reset() {
        if (debug) printf("Game::reset()\n");
        properties_.clear();
        graphics_.clear();
        flags_ = Flag();
    }

    // progresses every property owned by the entity by one step
    void progress() {
        if (debug) printf("Entity::progress()\n");
        for (size_t i = 0; i < properties_.size(); i++) {
            properties_[i]->progress();
        }
    }

    // draws every graphic owned by the entity at the given coordinates within the display
    void draw(DrawCoord dcoord) const {
        if (debug) printf("Entity::draw({%f, %f})\n", dcoord.x, dcoord.y);
        for (size_t i = 0; i < graphics_.size(); i++) {
            graphics_[i]->draw(dcoord.x,dcoord.y);
        }
    }

    // defines a new graphic owned and managed by the entity
    template <typename T, typename... Args>
    void graphic(Args... args) {
        if (debug) printf("Entity::graphic(...)\n");
        graphics_.emplace_back(new T(args...)); // or &args...
    }

    // defines a new property owned and managed by the entity
    template <typename T, typename... Args>
    void property(Args... args) {
        if (debug) printf("Entity::property(...)\n");
        properties_.emplace_back(new T(args...));
    }

    Flag flags() const { return flags_; }
    size_t id() const { return id_; }

    static inline bool debug = false;

private:

    size_t id_;
    Flag flags_;

    std::vector<std::shared_ptr<Graphic>> graphics_;
    std::vector<std::shared_ptr<Property>> properties_;

};


// get tiles to render from camera
// then translate tile position to display position
// then get entities to render from tile
// then pass display position to entities render(x,y)

// overhead of move construction
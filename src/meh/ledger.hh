#pragma once

#include <functional>
#include <memory.h>
#include <queue>
#include <unordered_map>
#include <vector>

#include "alxx/font.hh"
#include "component.hh"
#include "constants.hh"
#include "graphic.hh"

class Ledger {
public:

    Ledger() 
        : next_id_(0)
        , freed_ids_()
        , signatures_()
        , graphics_()
        // , components_()
    {}

    id_t create() {
        id_t id = next_id_;
        if (freed_ids_.empty()) {
            next_id_++;
        } else {
            id = freed_ids_.front();
            freed_ids_.pop();
        }

        if (id < signatures_.size()) signatures_.at(id).reset();
        else if (id > signatures_.size()) signatures_.resize(id+1);
        else signatures_.emplace_back();

        return id;
    }

    void erase(id_t id) {
        graphics_.erase(id);
        // components_.erase(id);
        signatures_.at(id).reset();
    }

    unsigned add_graphic(id_t id, Graphic *graphic) {
        auto range = graphics_.equal_range(id);
        unsigned index = 0;
        while(range.first != range.second) {
            index++;
            range.first++;
        }
        graphics_.emplace_hint(range.second, id, graphic);
    }

    unsigned add_component(id_t id, Component *component) {
        auto range = components_.equal_range(id);
        unsigned index = 0;
        while(range.first != range.second) {
            index++;
            range.first++;
        }
        components_.emplace_hint(range.second, id, component);
    }

    void add_signature(id_t id, signature_t sign) {
        signatures_.at(id) & sign;
    }

    signature_t get_signature(id_t id) {
        signatures_.at(id);
    }

    void system(cstr name, std::function<void(id_t, const Graphic&)> foo) const {
        for (auto entry : graphics_) {
            foo(entry.first, *entry.second);
        }
    }

    void system(std::function<void(id_t, Graphic&)> foo) {
        for (auto entry : graphics_) {
            foo(entry.first, *entry.second);
        }
    }

private:

    id_t next_id_;
    std::queue<id_t> freed_ids_;

    std::vector<signature_t> signatures_;
    std::unordered_multimap<id_t, std::shared_ptr<Graphic>> graphics_;
    std::unordered_multimap<id_t, std::shared_ptr<Component>> components_;

};

/**
 * template<T, Ts>
 * class Foo {
 *  Foo<T> foo;
 *  Foo<Ts> foo;
 * }
 **/
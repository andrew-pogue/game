#pragma once
#include <functional>
#include <optional>
#include <queue>
#include <vector>
#include "entity.hh"

// A data structure in which each entry is assigned a unique ID.
// It isn't resized when a an entry is removed, instead the associated
// ID is marked as 'freed' and the memory at that ID can be reused when
// a new entry is created. It is implemented internally with a vector.
class Manager {
public:

    Manager()
        : next_id_(0)
        , freed_ids_()
        , elements_()
    {
        if (debug) printf("Manager::Manager()\n");
    }

    ~Manager() {
        if (debug) printf("Manager::~Manager()\n");
    }

    size_t create() {
        if (debug) printf("Manager::create()\n");
        size_t id = 0;
        if (freed_ids_.empty()) {
            id = elements_.size();
            elements_.emplace_back(id);
            status_.emplace_back(true);
        } else {
            id = freed_ids_.front();
        }
        return id;
    }

    template <typename T, typename... Args>
    bool graphic(size_t id, Args... args) {
        if (debug) printf("Manager::graphic(%zi, ...)\n", id);
        if (!status_.at(id)) return false;
        elements_.at(id).graphic<T>(args...);
        return true;
    }

    template <typename T, typename... Args>
    bool property(size_t id, Args... args) {
        if (debug) printf("Manager::property(%zi, ...)\n", id);
        if (!status_.at(id)) return false;
        elements_.at(id).property<T>(args...);
        return true;
    }

    bool progress(size_t id) {
        if (debug) printf("Manager::progress(%zi)\n", id);
        if (!status_.at(id)) return false;
        elements_.at(id).progress();
        return true;
    }

    bool draw(size_t id, DrawCoord dcoord) const {
        if (debug) printf("Manager::draw(%zi, {%f, %f})\n", id, dcoord.x, dcoord.y);
        if (!status_.at(id)) return false;
        elements_.at(id).draw(dcoord);
        return true;
    }

    void remove(size_t id) {
        if (debug) printf("Manager::remove(%zi)\n", id);
        if (id >= elements_.size()) return;
        elements_.at(id).reset();
        status_.at(id) = false;
    }

    auto flags(size_t id) {
        if (debug) printf("Manager::sign(%zi)\n", id);
        if (!status_.at(id)) throw "id isn't associated with entity";
        return elements_.at(id).flags();
    }

    void reset() {
        if (debug) printf("Manager::reset()\n");
        elements_.clear();
        next_id_ = 0;
        while (!freed_ids_.empty()) {
            freed_ids_.pop();
        }
    }

    static inline bool debug = false;
    
private:

    size_t next_id_;
    std::queue<size_t> freed_ids_;
    // As long as Entity is small, I can avoid using Entity*
    std::vector<Entity> elements_;
    std::vector<bool> status_;

    // this class should not return a reference to entities
    // because the entities memory address moves when the
    // underlining vector resizes
    // unless.. Entity pointers are used instead 
    
};
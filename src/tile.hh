#pragma once
#include <unordered_map>

// The tile has every flag that its residents have.
class Tile {
public:

    void add(size_t id, Flag flags=0) {
        if (debug) printf("Tile::add(%zi)\n", id);
        residents_[id] = flags;
        flags_ |= flags;
    }

    void remove(size_t id) {
        if (debug) printf("Tile::remove(%zi)\n", id);
        if (!residents_.erase(id)) return;
        flags_ = 0;
        for (auto entry : residents_)
            flags_ |= entry.second;
    }

    bool has(size_t id) {
        if (debug) printf("Tile::has(%zi)\n", id);
        return residents_.count(id);
    }

    Flag flags() const {
        return flags_;
    }

    std::vector<size_t> residents() const {
        if (debug) printf("Tile::residents()\n");
        std::vector<size_t> result;
        for (auto entry : residents_)
            result.push_back(entry.first);
        return result;
    }

    static inline bool debug = false;

private:
    
    Flag flags_;
    std::unordered_map<size_t, Flag> residents_;

};

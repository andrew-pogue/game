#pragma once

#include "constants.hh"
#include <unordered_map>
#include <vector>

// An entity container. Represents a square area in the game world.
class Tile {
public:

    Tile() : signature_(0), residents_() {}

    void add(id_t id, signature_t sign) {
        signature_ |= sign;
        residents_.emplace(id, sign);
    }

    void remove(id_t id, signature_t sign) {
        // for each bit, check if another resident has that bit
        // if they do not, remove that bit from tile sign
        for (auto i = 0; i < sign.size(); i++) {
            if (!sign[i]) continue;
            for (auto r : residents_) {
                if (sign[i] & r.second[i]) {
                    signature_[i] = false;
                    break;
                }
            }
        }
    
        residents_.erase(id);
    }

    bool has(id_t id) const {
        return residents_.count(id);
    }

    // Returns true if for every ticked bit in the given signature,
    // the same bit is ticked in the tile's signature.
    bool matches(signature_t signature) const {
        return signature == (signature_ & signature);
    }

    signature_t get_signature() const {
        return signature_;
    }

    std::vector<id_t>&& get_residents() const {
        std::vector<id_t> result;
        for (auto r : residents_)
            result.push_back(r.first);
        return std::move(result);
    }

private:

    signature_t signature_;
    std::unordered_map<id_t, signature_t> residents_;

};
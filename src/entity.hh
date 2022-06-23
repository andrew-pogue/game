#pragma once
#include "constants.hh"
#include <queue>

class Entity {
protected:

    Entity(id_t id, signature_t sign = signature_t())
        : id_(id), sign_() {}

    virtual void update() = 0;
    virtual void render() const = 0;

    id_t get_id() const { return id_; }
    signature_t get_signature() const { return sign_; }

private:

    id_t id_;
    signature_t sign_;
    friend class EntityFactory;

};

class EntityFactory {
public:

    EntityFactory() : next_id_(0) {}

private:

    id_t next_id_;
    std::queue<id_t> freed_ids_;

    id_t allot() {
        if (freed_ids_.empty())
            return next_id_;
        id_t id = freed_ids_.front();
        freed_ids_.pop();
        return id;
    }
    
};
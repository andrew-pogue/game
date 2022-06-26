#pragma once

#include <functional>

class Command {
public:

    // The reason I use this instead of std::function directly
    // is because command.run() is nicer than command(),
    // and I want the default value of a command to be a
    // function that does nothing. Its also easier to extend
    // in the future if needed.

    using function_t = std::function<void(unsigned)>;
    
    Command(function_t&& foo = [](unsigned){}, int flags=0)
        : flags(flags)
        , foo_(foo)
    {
    }

    Command(const function_t& foo, int flags=0)
        : flags(flags)
        , foo_(foo)
    {
    }

    Command(const Command &other) 
        : flags(other.flags)
        , foo_(other.foo_)
    {
    }

    Command(Command &&other) 
        : flags(std::move(other.flags))
        , foo_(std::move(other.foo_))
    {
    }

    void run(unsigned entity) const {
        foo_(entity);
    }

    void operator=(const function_t& foo) {
        foo_ = foo;
    }

    void operator=(const Command& other) {
        foo_ = other.foo_;
        flags = other.flags;
    }

    int flags;

private:

    function_t foo_;

};

// Command      function object (returns void, takes void)
// Director     command factory, enables change to components
// Ledger       stores components, enables access to components
// Entity       API for EntityManager and ComponentManager
// 

// struct Command {
// public:
//     Command(auto foo) : foo_(foo) {}
//     virtual void run() { foo(); }
// private:
//     std::function<void()> foo_;
// };

// director
// overseer
// EntityManager, ComponentManager

// // command factory, enables change to components
// struct Director {
// public:

//     // reference a deallocated ledger?
//     Director(Ledger &ledger);

//     Command move(Entity entity, char direction) {
//         return Command([entity, move]{
//             auto move = entity.get<Move>();
//             if (!move) return;
//             move->dx += amount.x;
//             move->dy += amount.y;
//             move->dz += amount.z;
//         });
//     }

//     // teleport to the given destination, not default
//     // Command move(Entity entity, Position destination, flag=TELEPORT);

//     // use pathfinding algorithm to travel to destination, default
//     // Command move(Entity entity, Position destination, flag=TRAVEL);

// };

// entity.move(x,y,z)       ??
// commander.move(e, {x,y,z})

// action factory
// constructs move_left, move_right, move_up, move_down, and any others
// cons: any new commands need to be added to factory
// or.. make into free function, takes actor, returns command pointer
// command gets placed on queue
// conditional_commands? iff condition, run. else, dont run

// inline const Command = Action([](ecs::id_t actor){
//     auto move = ecs::get<Move>(actor);
//     if (move) move->dx -= 1;
// });

// inline const Action::act_t MOVE_RIGHT([](ecs::id_t actor){
//     auto move = ecs::get<Move>(actor);
//     if (move) move->dx += 1;
// });

// inline const Action::act_t MOVE_DOWN([](ecs::id_t actor){
//     auto move = ecs::get<Move>(actor);
//     if (move) move->dx -= 1;
// });

// inline const Action::act_t MOVE_UP([](ecs::id_t actor){
//     auto move = ecs::get<Move>(actor);
//     if (move) move->dx -= 1;
// });
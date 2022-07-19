#pragma once
// #include "constants.hh"

// class Move : public Coord {
// public:

//     // Move(int x, int y, int z, unsigned speed)
//     //     : Position(x,y,z), speed_(speed), cooldown_(0)
//     //     , direction_current_(0), direction_given_(0)
//     // {}

//     Move(float x, float y, unsigned speed)
//         : Coord(x,y), speed_(speed), cooldown_(0)
//         , direction_current_(0), direction_given_(0)
//     {}

//     void update(unsigned direction=0) {
//             direction_given_ |= direction;
//     }

//     void progress() {
//         if (!cooldown_) {
//             direction_current_ = direction_given_;
//             if (direction_current_) {
//                 cooldown_ = speed_;
//                 printf("direction: %u\n", direction_current_);
//             }
//         }

//         if (cooldown_) {
//             if (direction_current_ & NORTH)
//                 y_ -= TILE_SIZE / (float)speed_;
//             if (direction_current_ & SOUTH)
//                 y_ += TILE_SIZE / (float)speed_;
//             if (direction_current_ & EAST)
//                 x_ += TILE_SIZE / (float)speed_;
//             if (direction_current_ & WEST)
//                 x_ -= TILE_SIZE / (float)speed_;
//             cooldown_--;
//         }

//         direction_given_ = 0;
//     }

//     unsigned speed() const { return speed_; }
//     void speed(unsigned speed) { speed_ = speed; }

// private:

//     unsigned speed_;
//     unsigned cooldown_, direction_current_, direction_given_;

// };




// entity shouldn't have multiple of same component
// every component should have a signature attached to it
// signature should be set when component is added


// if signature & move
// cache[move][entity id].update(direction_given_)


// virtual bool move(direction) { return false; }
// bool move(direction) override { direction_given_ |= direction; return cooldown_; }

// entity.move(direction);
// entity.progress();

// not every entity has a move component
// but every entity can be passed the move command
// every entity is capable of owning the move component
// every enitty is capable of losing the move component

// composite framework?
// entity component system framework?
// virtual methods and inheritance?

// comand runs on every component with signature?

// overhead of pointers
// overhead of objects
// overhead of inheritance
// overhead of virtual and pure virtual
// overhead of templates

// data structure that uses void pointers
// stores unknown number of multiple different unknown types
// stores each unknown type in its own vector
// user asks for integer, structure returns integer
// user asks for char, structure returns char
// structure releases data?

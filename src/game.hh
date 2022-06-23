#pragma once

#include <bitset>

#include "alxx/display.hpp"
#include "alxx/event_queue.hpp"
#include "alxx/timer.hpp"
#include "constants.hh"
#include "entity.hh"
#include "font/font_map.hpp"
#include "io/keyboard.hh"
#include "io/mouse.hh"
#include "scene/scene.hh"

class Game {
public:

    Game() 
        : status_(0)
        , display_(WINDOW_WIDTH, WINDOW_HEIGHT)
        , event_queue_()
        , frame_timer_(1.0/30.0)
        , keyboard_()
        , mouse_(WINDOW_WIDTH/2, WINDOW_HEIGHT/2, 0)
        , factory_()
        , scene_({0,0,0})
    {
        display_[ALLEGRO_EVENT_DISPLAY_CLOSE] = [&](unsigned){
            status_[PLAY] = false;
        };

        keyboard_[ALLEGRO_KEY_ESCAPE] = [&](unsigned){
            status_[PLAY] = false;
        };
    }
    
    ~Game() {}
    
    void play() {
        status_[PLAY] = true;
        ALLEGRO_EVENT event;
        while(status_[PLAY]) {
            event_queue_.wait_for_event(&event);
            
            display_.update(event);
            keyboard_.update(event);
            mouse_.update(event);
            
            if (status_[RENDER]) {
                render();
            }
        }
    }

protected:

    const unsigned
        PLAY = 0,
        RENDER = 1;

    bool update() {
        
    }

    void render() {
        status_[RENDER] = false;
        al_clear_to_color(al_map_rgb(0,0,0));
        al_flip_display();
    }

    std::bitset<8> status_;
    Display display_;
    EventQueue event_queue_;
    Timer frame_timer_;
    Keyboard keyboard_;
    Mouse mouse_;
    EntityFactory factory_;
    Scene scene_;

};
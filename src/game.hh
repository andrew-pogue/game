#pragma once

#include <allegro5/allegro.h>
#include <bitset>
#include <iostream>

#include "alxx/display.hpp"
#include "alxx/event_queue.hpp"
#include "alxx/timer.hpp"
#include "constants.hh"
#include "entity.hh"
#include "font/font_map.hpp"
#include "glyh.hh"
#include "io/keyboard.hh"
#include "io/mouse.hh"
#include "scene/scene.hh"

class Game {
public:

    Game() 
        : status_(0)
        , display_(WINDOW_WIDTH, WINDOW_HEIGHT, "Game")
        , event_queue_()
        , frame_timer_(1.0/30.0)
        , keyboard_()
        , mouse_(WINDOW_WIDTH/2, WINDOW_HEIGHT/2, 0)
        , scene_({0,0,0})
    {
        event_queue_.register_source(al_get_keyboard_event_source());
        event_queue_.register_source(al_get_mouse_event_source());
        event_queue_.register_source(display_);
        event_queue_.register_source(frame_timer_);
        
        display_[ALLEGRO_EVENT_DISPLAY_CLOSE] = [&](unsigned){
            status_[PLAY] = false;
        };

        keyboard_[ALLEGRO_KEY_ESCAPE] = [&](unsigned){
            status_[PLAY] = false;
        };
    }
    
    ~Game() {
        printf("~Game()\n");
    }
    
    void play() {
        printf("play()\n");
        status_[PLAY] = true;
        ALLEGRO_EVENT event;

        Entity player("player", 0);
        auto font = al_create_builtin_font();
        player += new Glyph('@', font, "white");

        frame_timer_.start();
        while(status_[PLAY]) {
            event_queue_.wait_for_event(&event);

            display_.update(event);
            keyboard_.update(event);
            mouse_.update(event);

            player.update();
            this->update();
            
            if (event.type == ALLEGRO_EVENT_TIMER) {
                status_[RENDER] = true;
            }

            if (status_[RENDER] && event_queue_.is_empty()) {

                status_[RENDER] = false;
                al_clear_to_color(al_map_rgb(0,0,0));
                player.render((float)WINDOW_WIDTH/2.0f, (float)WINDOW_HEIGHT/2.0f);
                al_flip_display();

                // this->render();
            }
        }
    
        al_destroy_font(font);
        printf("Exit\n");
    }

protected:

    const unsigned
        PLAY = 0,
        RENDER = 1;

    void update() {
        for (auto command : display_.get_commands()) {
            command.run(0);
        }

        for (auto command : keyboard_.get_commands()) {
            command.run(0);
        }

        for (auto command : mouse_.get_commands()) {
            command.run(0);
        }
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
    Scene scene_;

};